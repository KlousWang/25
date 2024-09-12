#include<iostream>
#include<stdexcept>
using namespace std;
template<typename T,size_t MAX_SIZE>
class circularQueue {
private:
	T data[MAX_SIZE];//�洢Ԫ�ص�����
	size_t front;
	size_t rear;
	size_t size;

public:
	circularQueue():front(0),rear(0),size(0){}

	//
	bool isEmpty() const{
		return size == 0;
	}

	bool isFull() {
		return size == MAX_SIZE;
	}

	void enqueue(int value);
	T dequeue();
	T peekrear()const;
};

template<typename T, size_t MAX_SIZE>
void circularQueue<T, MAX_SIZE>::enqueue(int value)
{
	if (isFull()) {
		cout<<"queue is full"<<endl;
	}
	data[rear] = value;
	rear = (rear + 1) % MAX_SIZE;
	++size;
}

template<typename T, size_t MAX_SIZE>
T circularQueue<T, MAX_SIZE>::dequeue()
{
	if (isEmpty()) {
		cout << "queue is empty" << endl;
	}
	T Value = data[front];
	front = (front + 1) % MAX_SIZE;
	--size;
	return Value
}

template<typename T, size_t MAX_SIZE>
T circularQueue<T, MAX_SIZE>::peekrear() const
{
	if (isEmpty())
		cout << "queue is empty" << endl;
	return data[front];
}

int main() {
	circularQueue<int, 5> queue;

	// ��Ӳ���
	queue.enqueue(1);
	queue.enqueue(2);
	queue.enqueue(3);

	std::cout << "Front element: " << queue.peekrear() << std::endl;

	// ���Ӳ���
	std::cout << "Dequeued: " << queue.dequeue() << std::endl;
	std::cout << "Dequeued: " << queue.dequeue() << std::endl;

	// �ٴ���Ӳ���
	queue.enqueue(4);
	queue.enqueue(5);

	while (!queue.isEmpty()) {
		std::cout << "Dequeued: " << queue.dequeue() << std::endl;
	}

	return 0;
}