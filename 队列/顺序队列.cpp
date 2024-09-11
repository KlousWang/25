#include<iostream>

using namespace std;

class Queue {
private:
	int* queueArrary;//队列存储的数组
	int front;//对头指针
	int reaer;//队尾指针
	int capacity;//队列容量
	int count;//当前队列中的元素数量
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

// 测试顺序队列的代码
int main() {
	Queue queue(5);  // 创建一个容量为5的顺序队列

	// 入队操作
	queue.enqueue(10);
	queue.enqueue(20);
	queue.enqueue(30);
	queue.enqueue(40);
	queue.enqueue(50);

	// 队列已满，无法再添加
	queue.enqueue(60);

	// 输出队列中的元素
	cout << "Front element: " << queue.peekfront() << endl;
	cout << "Rear element: " << queue.peekrear() << endl;

	// 出队操作
	cout << "Dequeued element: " << queue.dequeue() << endl;
	cout << "Dequeued element: " << queue.dequeue() << endl;

	// 查看队列状态
	cout << "Queue size: " << queue.size() << endl;

	// 再次入队
	queue.enqueue(60);
	queue.enqueue(70);

	// 查看队列状态
	cout << "Front element after more enqueues: " << queue.peekfront() << endl;
	cout << "Rear element after more enqueues: " << queue.peekrear() << endl;

	return 0;
}