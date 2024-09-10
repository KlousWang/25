#include <iostream>
using namespace std;

class StaticStack {
private:
    int* stackArray;   // ���ڴ洢ջԪ�ص�����
    int capacity;      // ջ���������
    int top;           // ջ��ָ�룬ָ��ǰջ��Ԫ�ص�λ��

public:
    // ���캯������ʼ��ջ
    StaticStack(int size) : capacity(size), top(-1) {
        stackArray = new int[capacity];  // ��������Ϊ size ������
    }

    // �����������ͷ��ڴ�
    ~StaticStack() {
        delete[] stackArray;
    }

    // ���ջ�Ƿ�Ϊ��
    bool isEmpty() const {
        return top == -1;
    }

    // ���ջ�Ƿ�����
    bool isFull() const {
        return top == capacity - 1;
    }

    // ��ջ��ѹ��Ԫ��
    void push(int value) {
        if (isFull()) {
            cout << "Stack is full! Cannot push " << value << endl;
            return;
        }
        stackArray[++top] = value;
    }

    // ��ջ�е���Ԫ��
    int pop() {
        if (isEmpty()) {
            cout << "Stack is empty! Cannot pop." << endl;
            return -1;  // ����һ������ֵ������ջ�ǿյ�
        }
        return stackArray[top--];
    }

    // ��ȡջ��Ԫ��
    int peek() const {
        if (isEmpty()) {
            cout << "Stack is empty! Cannot peek." << endl;
            return -1;  // ����һ������ֵ������ջ�ǿյ�
        }
        return stackArray[top];
    }

    // ��ȡջ�ĵ�ǰ��С
    int size() const {
        return top + 1;
    }
};

// ���Ծ�̬ջ�Ĵ���
int main() {
    StaticStack stack(5);  // ����һ������Ϊ5��ջ

    // ѹ��Ԫ��
    stack.push(10);
    stack.push(20);
    stack.push(30);

    cout << "Stack size: " << stack.size() << endl;  // ���ջ�Ĵ�С

    // ����Ԫ��
    cout << "Popped element: " << stack.pop() << endl;

    // �鿴ջ��Ԫ��
    cout << "Top element: " << stack.peek() << endl;

    // �ٴ�ѹ��Ԫ��
    stack.push(40);
    stack.push(50);
    stack.push(60);  // ����ջ���ˣ��޷�ѹ��

    cout << "Stack size after pushes: " << stack.size() << endl;

    // ��������Ԫ��
    while (!stack.isEmpty()) {
        cout << "Popped element: " << stack.pop() << endl;
    }

    return 0;
}
