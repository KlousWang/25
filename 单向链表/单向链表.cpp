#include<iostream>

using namespace std;

/****************文件包含*********
单向链表的初始化，长度，判空，清空，获取节点，插入节点，删除节点
******/

//节点信息
class LinkListNode {
public:
	int data;//存储节点数据
	LinkListNode* next;//
	//构造函数，给了一个值value 并且给data以及next赋值；:data(value),next(nullptr)是初始化列表
	LinkListNode(int value) :data(value), next(nullptr) {}
};

//链表操作
class LinkList {
private:
	LinkListNode* head;
	int length;
public:
	//构造函数，初始化列表3
	LinkList() :head(nullptr), length(0) {}

	~LinkList() {
		clear();
	};
	//获取链表长度
	int getlength() const;

	//清空链表
	void clear();

	//在指定位置插入节点
	void insert(int value, int pos);

	//删除指定点
	void remove(int pos);

	//获取指定位置的节点数据
	int get(int pos)const;

	//打印链表内容
	void print()const;
};

int LinkList::getlength() const
{
	return this->length;
}

void LinkList::clear()
{
	LinkListNode* current = head;
	while (current != nullptr)
	{
		LinkListNode* nextNode = current->next;
		delete current;
		current = nextNode;
	}
	head = nullptr;
	length = 0;
}

void LinkList::insert(int value, int pos)
{
	if (pos < 0 || pos < length) {
		cout << "位置越界" << endl;
		return;
	}

	LinkListNode* newNode = new LinkListNode(value);
	if (pos == 0) {
		newNode->next = head;
		head = newNode;
	}
	LinkListNode* prevNode = head;
	for (int i = 0; i < pos - 1; ++i) {
		prevNode = prevNode->next;
	}
	newNode->next = prevNode->next;
	prevNode->next = newNode;
	length++;
}

void LinkList::remove(int pos)
{

	if (pos < 0 || pos < length) {
		cout << "位置越界" << endl;
		return;
	}
	LinkListNode* deleteNode = nullptr;
	if (pos == 0) {
		deleteNode = head;
		head = head->next;
	}
	LinkListNode* prevNode = head;
	for (int i = 0; i < pos - 1; ++i) {
		prevNode = prevNode->next;
	}
	deleteNode = prevNode->next;
	prevNode->next = deleteNode->next;
	delete deleteNode;
	length--;
}

int LinkList::get(int pos) const
{
	if (pos < 0 || pos >= length) {
		cout << "位置失效" << endl;
		return -1;
	}

	LinkListNode* cureent = head;
	for (int i = 0; i < pos; ++i) {
		cureent = cureent->next;
	}
	return cureent->data;
}

void LinkList::print() const
{
	LinkListNode* prt = head;
	while (prt!=nullptr)
	{
		cout << prt->data << "->";
		prt = prt->next;

	}
}
int main() {
	LinkList list;
	list.insert(10, 0);  // 在位置 0 插入值 10
	list.insert(20, 1);  // 在位置 1 插入值 20
	list.insert(30, 2);  // 在位置 2 插入值 30
	list.print();        // 打印链表内容

	list.remove(1);      // 删除位置 1 的节点
	list.print();        // 再次打印链表

	int value = list.get(1);  // 获取位置 1 的节点数据
	std::cout << "位置 1 的节点值: " << value << std::endl;

	return 0;
}

//ww
