#include<iostream>

using namespace std;

//创造节点信息
class DoublyLinkedNode {
public:
	int data;//存储节点信息
	DoublyLinkedNode* next;//指向后一个的指针
	DoublyLinkedNode* prev;//指向前一个的指针

	//构造函数
	DoublyLinkedNode(int value):data(value),next(nullptr), prev(nullptr) {}
};

//双向链表
class DoublyLinkedList {
private:
	DoublyLinkedNode* head;//头节点
	DoublyLinkedNode* tail;//尾节点
	int length;//长度
public:
	//构造函数
	DoublyLinkedList() :head(nullptr), tail(nullptr), length(0){}

	~DoublyLinkedList() { clear(); }
	
	//获取链表长度
	int getLength()const;

	//判断链表是否为空
	bool isEmpty()const;
	
	//清空链表
	void clear();

	//在链表头部插入节点
	void insertHead(int value);
};

int DoublyLinkedList::getLength() const
{
	return length;
}

bool DoublyLinkedList::isEmpty() const
{
	return length ==0;
}

void DoublyLinkedList::clear()
{
	DoublyLinkedNode* current = head;
	 while(current!= nullptr) {
		 DoublyLinkedNode* nextNode = current->next;
		 delete current;
		 current = nextNode;
	}
	 head = nullptr;
	 tail = nullptr;
	 length = 0;
}

void DoublyLinkedList::insertHead(int value)
{
	DoublyLinkedNode* newNode = new DoublyLinkedNode(value);
	if (isEmpty) {
		head = tail = newNode;
	}
	newNode = head;
	head->prev = newNode;
	head = newNode;
	length++;
}
