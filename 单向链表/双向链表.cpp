#include<iostream>

using namespace std;

//����ڵ���Ϣ
class DoublyLinkedNode {
public:
	int data;//�洢�ڵ���Ϣ
	DoublyLinkedNode* next;//ָ���һ����ָ��
	DoublyLinkedNode* prev;//ָ��ǰһ����ָ��

	//���캯��
	DoublyLinkedNode(int value):data(value),next(nullptr), prev(nullptr) {}
};

//˫������
class DoublyLinkedList {
private:
	DoublyLinkedNode* head;//ͷ�ڵ�
	DoublyLinkedNode* tail;//β�ڵ�
	int length;//����
public:
	//���캯��
	DoublyLinkedList() :head(nullptr), tail(nullptr), length(0){}

	~DoublyLinkedList() { clear(); }
	
	//��ȡ������
	int getLength()const;

	//�ж������Ƿ�Ϊ��
	bool isEmpty()const;
	
	//�������
	void clear();

	//������ͷ������ڵ�
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
