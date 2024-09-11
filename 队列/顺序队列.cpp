#include<iostream>

using namespace std;

class Queue {
private:
	int* queueArrary;//���д洢������
	int front;//��ͷָ��
	int reaer;//��βָ��
	int capacity;//��������
	int count;//��ǰ�����е�Ԫ������
public:
	Queue(int size) :capacity(size), front(0), reaer(-1), count(0) { queueArrary = new int[capacity]; }

	~Queue() { delete[]queueArrary; }

	//
	bool isEmpty()const {
		return count == 0;

	}

	bool isFull()const {
		return count == capacity;
	}

	void enqueue(int value) {
		if (isFull()) {
			cout << "queue full" << endl;
		}
		reaer = (reaer + 1) % capacity;
		queueArrary[reaer] = value;
		count++;
	}

	int dequeue() {
		if (isEmpty()) {
			cout << "queue isempty" << endl;
			return -1;
		}
		int value = queueArrary[front];
		front = (front + 1) % capacity;
		count--;
		return value;
	}
	//
	int size()const {
		return count;
	}

	int peekfront()const {
		if (isEmpty()) {
			cout << "queue is empty" << endl;
			return-1;
		}
		return queueArrary[front];
	}

	int peekrear()const {
		if (isEmpty()) {
			cout << "queue is empty" << endl;
			return -1;
		}
		return queueArrary[reaer];
	}

};

// ����˳����еĴ���
int main() {
	Queue queue(5);  // ����һ������Ϊ5��˳�����

	// ��Ӳ���
	queue.enqueue(10);
	queue.enqueue(20);
	queue.enqueue(30);
	queue.enqueue(40);
	queue.enqueue(50);

	// �����������޷������
	queue.enqueue(60);

	// ��������е�Ԫ��
	cout << "Front element: " << queue.peekfront() << endl;
	cout << "Rear element: " << queue.peekrear() << endl;

	// ���Ӳ���
	cout << "Dequeued element: " << queue.dequeue() << endl;
	cout << "Dequeued element: " << queue.dequeue() << endl;

	// �鿴����״̬
	cout << "Queue size: " << queue.size() << endl;

	// �ٴ����
	queue.enqueue(60);
	queue.enqueue(70);

	// �鿴����״̬
	cout << "Front element after more enqueues: " << queue.peekfront() << endl;
	cout << "Rear element after more enqueues: " << queue.peekrear() << endl;

	return 0;
}