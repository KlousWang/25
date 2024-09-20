#include<iostream>
using namespace std;

template<typename T>

struct Node
{
	T data;
	Node* next;
	Node(T val):data(val),next(nullptr){}
};

template<typename T>
class LinkQueue {
private:
	Node<T>* front;
	Node<T>* rear;
	int size;

public:
	LinkQueue():front(nullptr),rear(nullptr),size(0){}

	~LinkQueue() {
		while (!is_empty())
		{
			dequeue();
		}
	}

	bool is_empty()const {
		return size == 0;
	}

	int getsize()const {
		return size;
	}

	void enqueue(T value) {
		Node<T>* newNode = new Node<T>(value);
		if (is_empty()) {
			front = rear = newNode;
		}
		else
		{
			rear->next = newNode;
			rear = newNode;
		}
		size++;

	}

	T dequeue() {
		if (is_empty()) {
			throw runtime_error("����Ϊ�գ��޷�����");
		}

		Node<T>* temp = front;

		T  value = front->data;
		front = front->next;

		delete temp;

		if (front == nullptr) {
			rear = nullptr;
		}
		size--;
		return value;
	}

	T peek()const {
		if (is_empty()) {
			throw runtime_error("����Ϊ�գ��޷���ȡͷ��Ԫ��");
		}
		return front->data;
	}

	void printQueue()const {
		Node<T>* current = front;
		while (current != nullptr) {
			cout << current->data << " ";
			current = current->next;
		}
		cout << endl;
		{

		}
	}
};

int main() {
	LinkQueue<int>que;
	que.enqueue(10);
	que.enqueue(20);
	que.enqueue(30);

	cout << "�����е�Ԫ��:";
	que.printQueue();


}