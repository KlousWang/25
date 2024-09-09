#include<iostream>
using namespace std;

//�ڵ���
class circularLinkedNode {
public:
	int data;
	circularLinkedNode* next;

	//���캯��
	circularLinkedNode(int value):data(value),next(nullptr){}
};


//����������
class circularLinkerList {
private:
	circularLinkedNode* head;
	circularLinkedNode* tail;
	int length;

public:

	//���캯��
	circularLinkerList():head(nullptr),tail(nullptr),length(0){}

	//��������
	~circularLinkerList() {
		clear();
	}

	//��ȡ������
	int getLength() {
		return length;
	}
	//�ж������Ƿ�Ϊ��
	bool isEmpty()const {
		return length == 0;
	}
	//�������
	void clear();
	//������ĩβ���һ���½ڵ�
	void append(int value);
	//ɾ��ָ���ڵ�
	void deleteValue(int value);
	//��ӡ����
	void printList()const;
};
int main() {
	circularLinkerList list;
	list.append(10);
	list.append(20);
	list.append(30);
	list.append(40);
	list.append(50);

	cout << "circular linked list:";
	list.printList();

	//
	cout << "delet node with 30" << endl;
	list.deleteValue(30);
	list.printList();

	//
	cout << "delere trail node" << endl;
	list.deleteValue(40);
	list.printList();

}

void circularLinkerList::clear() 
{
	if (isEmpty())return;

	circularLinkedNode* current = head;
	do
	{
		circularLinkedNode* nextNode = current->next;
		delete current;
		current = nextNode;
	} while (current!=head);
	head = tail = nullptr;
	length = 0;
}


//������ĩβ���һ���½ڵ�
void circularLinkerList::append(int value)
{
	circularLinkedNode* newNode = new circularLinkedNode(value);
	if (isEmpty()) {
		head = tail = newNode;
	}
	tail->next = newNode;
	tail = newNode;
	tail->next = head;

	length++;
}

void circularLinkerList::deleteValue(int value)
{
	if (isEmpty()) {
		cout << "��������Ϊ��" << endl;
		return;
	}

	circularLinkedNode* current = head;
	circularLinkedNode* prev = nullptr;

	//ɾ������ͷ�ڵ�
	if (head->data == value) {
		if (head ==tail)
		{
			delete head;
			head = tail = nullptr;
		}
		head = head->next;
		tail->next = head;
		delete current;
		length--;
		return;
	}

	//��������Ѱ��Ҫɾ���Ľڵ�
	do
	{
		prev = current;
		current = current->next;
		if (current->data == value) {
			prev->next = current->next;
			//���ɾ������β�ڵ�
			if (current == tail) {
				tail = prev;
				tail->next = head;
			}
			delete current;
			length--;
			return;

		}
	} while (current !=head);
	cout << "Node with value" << value << "not found" << endl;
}

void circularLinkerList::printList() const
{
	if (isEmpty()) {
		cout << "List is empty" << endl;
		return;
	}
	circularLinkedNode* current = head;
	do
	{
		cout << current->data << "->";
		current = current->next;
	} while (current!=head);
	cout << "(back to head" <<head->data << ")" << endl;
}

