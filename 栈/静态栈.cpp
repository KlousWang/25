#include <iostream>
using namespace std;

class StaticStack {
private:
    int* stackArray;   // 用于存储栈元素的数组
    int capacity;      // 栈的最大容量
    int top;           // 栈顶指针，指向当前栈顶元素的位置

public:
    // 构造函数，初始化栈
    StaticStack(int size) : capacity(size), top(-1) {
        stackArray = new int[capacity];  // 分配容量为 size 的数组
    }

    // 析构函数，释放内存
    ~StaticStack() {
        delete[] stackArray;
    }

    // 检查栈是否为空
    bool isEmpty() const {
        return top == -1;
    }

    // 检查栈是否已满
    bool isFull() const {
        return top == capacity - 1;
    }

    // 向栈中压入元素
    void push(int value) {
        if (isFull()) {
            cout << "Stack is full! Cannot push " << value << endl;
            return;
        }
        stackArray[++top] = value;
    }

    // 从栈中弹出元素
    int pop() {
        if (isEmpty()) {
            cout << "Stack is empty! Cannot pop." << endl;
            return -1;  // 返回一个错误值，表明栈是空的
        }
        return stackArray[top--];
    }

    // 获取栈顶元素
    int peek() const {
        if (isEmpty()) {
            cout << "Stack is empty! Cannot peek." << endl;
            return -1;  // 返回一个错误值，表明栈是空的
        }
        return stackArray[top];
    }

    // 获取栈的当前大小
    int size() const {
        return top + 1;
    }
};

// 测试静态栈的代码
int main() {
    StaticStack stack(5);  // 创建一个容量为5的栈

    // 压入元素
    stack.push(10);
    stack.push(20);
    stack.push(30);

    cout << "Stack size: " << stack.size() << endl;  // 输出栈的大小

    // 弹出元素
    cout << "Popped element: " << stack.pop() << endl;

    // 查看栈顶元素
    cout << "Top element: " << stack.peek() << endl;

    // 再次压入元素
    stack.push(40);
    stack.push(50);
    stack.push(60);  // 由于栈满了，无法压入

    cout << "Stack size after pushes: " << stack.size() << endl;

    // 弹出所有元素
    while (!stack.isEmpty()) {
        cout << "Popped element: " << stack.pop() << endl;
    }

    return 0;
}
