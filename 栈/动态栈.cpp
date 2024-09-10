#include<iostream>

using namespace std;
class DynamicStack {
private:
	int* stackArry;
	int capacity;
	int top;

	void resize() {
		int newCapacity = capacity * 2;
		int* newArraty = new int[newCapacity];

		for (int i = 0; i < capacity; ++i) {
			newArraty[i] = stackArry[i];
		}

		//ɾ���ɵ����ݣ�ָ���µ�����
		delete[]stackArry;

		stackArry = newArraty;
		capacity = newCapacity;
	}
public:
	DynamicStack(int size = 10) :capacity(size), top(-1) {
		stackArry = new int[capacity];
	}

	~DynamicStack() {
		delete[] stackArry;
	}
	bool isEmpty()const {
		return top == -1;
	}

	void push(int value) {
		if (top == capacity - 1) {
			resize();
		}
		stackArry[++top] = value;
	}

	int pop() {
		if (isEmpty()) {
			cout << "stack is empty" << endl;
			return -1;
		}
		return stackArry[top--];
	}

	int peek()const {
		if (isEmpty()) {
			cout << "stack is emty" << endl;
			return -1;
		}
		return stackArry[top];

	}

	int size()const {
		return top + 1;
	}
};
int main() {
		DynamicStack stack(5);  // ��ʼ����Ϊ 5 �Ķ�̬ջ

		// ѹ��Ԫ��
		stack.push(10);
		stack.push(20);
		stack.push(30);
		stack.push(40);
		stack.push(50);

		// ������չ����
		stack.push(60);  // ����ջ���ˣ��ᴥ�� resize()

		cout << "Stack size: " << stack.size() << endl;

		// �鿴ջ��Ԫ��
		cout << "Top element: " << stack.peek() << endl;

		// ����Ԫ��
		cout << "Popped element: " << stack.pop() << endl;
		cout << "Popped element: " << stack.pop() << endl;

		cout << "Stack size after pops: " << stack.size() << endl;

		return 0;
}