#include<iostream>
using namespace std;

//节点类
class circularLinkedNode {
public:
	int data;
	circularLinkedNode* next;

	//构造函数
	circularLinkedNode(int value):data(value),next(nullptr){}
};


//环形链表类
class circularLinkerList {
private:
	circularLinkedNode* head;
	circularLinkedNode* tail;
	int length;

public:

	//构造函数
	circularLinkerList():head(nullptr),tail(nullptr),length(0){}

	//析构函数
	~circularLinkerList() {
		clear();
	}

	//获取链表长度
	int getLength() {
		return length;
	}
	//判断链表是否为空
	bool isEmpty()const {
		return length == 0;
	}
	//清空链表
	void clear();
	//在链表末尾添加一个新节点
	void append(int value);
	//删除指定节点
	void deleteValue(int value);
	//打印链表
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


//在链表末尾添加一个新节点
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
		cout << "环形链表为空" << endl;
		return;
	}

	circularLinkedNode* current = head;
	circularLinkedNode* prev = nullptr;

	//删除的是头节点
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

	//遍历链表寻找要删除的节点
	do
	{
		prev = current;
		current = current->next;
		if (current->data == value) {
			prev->next = current->next;
			//如果删除的是尾节点
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

