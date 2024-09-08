#include<iostream>

using namespace std;

/****************�ļ�����*********
��������ĳ�ʼ�������ȣ��пգ���գ���ȡ�ڵ㣬����ڵ㣬ɾ���ڵ�
******/

//�ڵ���Ϣ
class LinkListNode {
public:
	int data;//�洢�ڵ�����
	LinkListNode* next;//
	//���캯��������һ��ֵvalue ���Ҹ�data�Լ�next��ֵ��:data(value),next(nullptr)�ǳ�ʼ���б�
	LinkListNode(int value) :data(value), next(nullptr) {}
};

//�������
class LinkList {
private:
	LinkListNode* head;
	int length;
public:
	//���캯������ʼ���б�3
	LinkList() :head(nullptr), length(0) {}

	~LinkList() {
		clear();
	};
	//��ȡ������
	int getlength() const;

	//�������
	void clear();

	//��ָ��λ�ò���ڵ�
	void insert(int value, int pos);

	//ɾ��ָ����
	void remove(int pos);

	//��ȡָ��λ�õĽڵ�����
	int get(int pos)const;

	//��ӡ��������
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
		cout << "λ��Խ��" << endl;
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
		cout << "λ��Խ��" << endl;
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
		cout << "λ��ʧЧ" << endl;
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
	list.insert(10, 0);  // ��λ�� 0 ����ֵ 10
	list.insert(20, 1);  // ��λ�� 1 ����ֵ 20
	list.insert(30, 2);  // ��λ�� 2 ����ֵ 30
	list.print();        // ��ӡ��������

	list.remove(1);      // ɾ��λ�� 1 �Ľڵ�
	list.print();        // �ٴδ�ӡ����

	int value = list.get(1);  // ��ȡλ�� 1 �Ľڵ�����
	std::cout << "λ�� 1 �Ľڵ�ֵ: " << value << std::endl;

	return 0;
}

//ww
