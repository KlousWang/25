#include<iostream>
#include<vector>
#include<memory>
using namespace std;

class GLNode {
public:
	//当前节点是原子还是子表
	enum NodeType{ATOM,LIST};

	//构造原子节点
	GLNode(char atom) :tag(ATOM), atom(atom) {}

	//构造子表节点
	GLNode(vector<shared_ptr<GLNode>>elements):tag(LIST),elements(elements){}

	//输出节点内容
	void print()const;
	//复制广义表
	shared_ptr<GLNode>copy()const;  //shared_Ptr 自动管理动态分配的对象
private:
	NodeType tag;//节点类型
	char atom;//原子值(如果是原子节点)
	vector<shared_ptr<GLNode>>elements;//子表元素(如果是子表节点)

};


void GLNode::print() const  //添加const的作用是：函数承诺不修改对象的任何成员变量
{
	if (tag == ATOM) {
		cout << atom;
	}
	else if(tag ==LIST)
	{
		cout << "(";
		for (size_t i = 0; i < elements.size(); ++i)
		{
			elements[i]->print();
			if (i < elements.size() - 1) {
				cout << ",";
			}
		}
		cout << ")";
	}
	
}

shared_ptr<GLNode> GLNode::copy() const
{
	if (tag == ATOM) {
		return make_shared<GLNode>(atom);//make_shared 是 C++11 引入的一个用于创建 shared_ptr 的标准库函数。
		                                 //它提供了一种高效、安全的方式来分配内存并创建一个 shared_ptr，用于管理该内存
	}
	vector < shared_ptr<GLNode>>copiedElements;
	for (const auto& elem : elements) { //elem是对elements的引用
		copiedElements.push_back(elem->copy());
	}
	return make_shared<GLNode>(copiedElements);
}

int main() {
	//创建广义表（a,(b,(c,d))）
	auto c = make_shared<GLNode>(vector<shared_ptr<GLNode>>{
		make_shared<GLNode>('a'),
			make_shared<GLNode>(vector<shared_ptr<GLNode>>{
			make_shared<GLNode>('b'),
				make_shared<GLNode>(vector<shared_ptr<GLNode>>{
				make_shared<GLNode>('c'),
					make_shared<GLNode>('d')
			})
		})
	});


	//复制广义表
	auto T = c->copy();

	//输出原始广义表和复制的广义表
	cout << "Original list:";
	c->print();
	cout << "nCopied list:";
	T->print();
	cout << endl;

	return 0;
}
