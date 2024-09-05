#include<iostream>
#include<vector>
#include<memory>
using namespace std;

class GLNode {
public:
	//��ǰ�ڵ���ԭ�ӻ����ӱ�
	enum NodeType{ATOM,LIST};

	//����ԭ�ӽڵ�
	GLNode(char atom) :tag(ATOM), atom(atom) {}

	//�����ӱ�ڵ�
	GLNode(vector<shared_ptr<GLNode>>elements):tag(LIST),elements(elements){}

	//����ڵ�����
	void print()const;
	//���ƹ����
	shared_ptr<GLNode>copy()const;  //shared_Ptr �Զ�����̬����Ķ���
private:
	NodeType tag;//�ڵ�����
	char atom;//ԭ��ֵ(�����ԭ�ӽڵ�)
	vector<shared_ptr<GLNode>>elements;//�ӱ�Ԫ��(������ӱ�ڵ�)

};


void GLNode::print() const  //���const�������ǣ�������ŵ���޸Ķ�����κγ�Ա����
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
		return make_shared<GLNode>(atom);//make_shared �� C++11 �����һ�����ڴ��� shared_ptr �ı�׼�⺯����
		                                 //���ṩ��һ�ָ�Ч����ȫ�ķ�ʽ�������ڴ沢����һ�� shared_ptr�����ڹ�����ڴ�
	}
	vector < shared_ptr<GLNode>>copiedElements;
	for (const auto& elem : elements) { //elem�Ƕ�elements������
		copiedElements.push_back(elem->copy());
	}
	return make_shared<GLNode>(copiedElements);
}

int main() {
	//���������a,(b,(c,d))��
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


	//���ƹ����
	auto T = c->copy();

	//���ԭʼ�����͸��ƵĹ����
	cout << "Original list:";
	c->print();
	cout << "nCopied list:";
	T->print();
	cout << endl;

	return 0;
}
