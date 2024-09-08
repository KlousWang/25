#include <iostream>

// 节点结构
class DoublyLinkedListNode {
public:
    int data;  // 节点数据
    DoublyLinkedListNode* prev;  // 指向前一个节点
    DoublyLinkedListNode* next;  // 指向下一个节点

    DoublyLinkedListNode(int value) : data(value), prev(nullptr), next(nullptr) {}
};

// 双向链表类
class DoublyLinkedList {
private:
    DoublyLinkedListNode* head;  // 头节点
    DoublyLinkedListNode* tail;  // 尾节点
    int length;

public:
    // 构造函数，初始化空链表
    DoublyLinkedList() : head(nullptr), tail(nullptr), length(0) {}

    // 析构函数，释放链表内存
    ~DoublyLinkedList() {
        clear();
    }

    // 获取链表长度
    int getLength() const {
        return length;
    }

    // 判断链表是否为空
    bool isEmpty() const {
        return length == 0;
    }

    // 清空链表
    void clear() {
        DoublyLinkedListNode* current = head;
        while (current != nullptr) {
            DoublyLinkedListNode* nextNode = current->next;
            delete current;  // 释放当前节点的内存
            current = nextNode;
        }
        head = nullptr;
        tail = nullptr;
        length = 0;
    }

    // 在链表头部插入节点
    void insertAtHead(int value) {
        DoublyLinkedListNode* newNode = new DoublyLinkedListNode(value);
        if (isEmpty()) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        length++;
    }

    // 在链表尾部插入节点
    void insertAtTail(int value) {
        DoublyLinkedListNode* newNode = new DoublyLinkedListNode(value);
        if (isEmpty()) {
            head = tail = newNode;
        } else {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
        length++;
    }

    // 在指定位置插入节点
    void insertAtPosition(int value, int pos) {
        if (pos < 0 || pos > length) {
            std::cout << "位置无效" << std::endl;
            return;
        }

        if (pos == 0) {
            insertAtHead(value);
        } else if (pos == length) {
            insertAtTail(value);
        } else {
            DoublyLinkedListNode* newNode = new DoublyLinkedListNode(value);
            DoublyLinkedListNode* current = head;
            for (int i = 0; i < pos - 1; ++i) {
                current = current->next;
            }
            newNode->next = current->next;
            newNode->prev = current;
            current->next->prev = newNode;
            current->next = newNode;
            length++;
        }
    }

    // 删除链表头部节点
    void removeAtHead() {
        if (isEmpty()) {
            std::cout << "链表为空，无法删除" << std::endl;
            return;
        }

        DoublyLinkedListNode* deleteNode = head;
        if (head == tail) {  // 只有一个节点的情况
            head = tail = nullptr;
        } else {
            head = head->next;
            head->prev = nullptr;
        }
        delete deleteNode;
        length--;
    }

    // 删除链表尾部节点
    void removeAtTail() {
        if (isEmpty()) {
            std::cout << "链表为空，无法删除" << std::endl;
            return;
        }

        DoublyLinkedListNode* deleteNode = tail;
        if (head == tail) {  // 只有一个节点的情况
            head = tail = nullptr;
        } else {
            tail = tail->prev;
            tail->next = nullptr;
        }
        delete deleteNode;
        length--;
    }

    // 删除指定位置的节点
    void removeAtPosition(int pos) {
        if (pos < 0 || pos >= length) {
            std::cout << "位置无效" << std::endl;
            return;
        }

        if (pos == 0) {
            removeAtHead();
        } else if (pos == length - 1) {
            removeAtTail();
        } else {
            DoublyLinkedListNode* current = head;
            for (int i = 0; i < pos; ++i) {
                current = current->next;
            }
            current->prev->next = current->next;
            current->next->prev = current->prev;
            delete current;
            length--;
        }
    }

    // 从头遍历并打印链表
    void printFromHead() const {
        DoublyLinkedListNode* current = head;
        while (current != nullptr) {
            std::cout << current->data << " <-> ";
            current = current->next;
        }
        std::cout << "null" << std::endl;
    }

    // 从尾遍历并打印链表
    void printFromTail() const {
        DoublyLinkedListNode* current = tail;
        while (current != nullptr) {
            std::cout << current->data << " <-> ";
            current = current->prev;
        }
        std::cout << "null" << std::endl;
    }
};

int main() {
    DoublyLinkedList list;

    // 在头部插入节点
    list.insertAtHead(10);
    list.insertAtHead(20);
    list.insertAtHead(30);
    list.printFromHead();  // 输出: 30 <-> 20 <-> 10 <-> null

    // 在尾部插入节点
    list.insertAtTail(40);
    list.insertAtTail(50);
    list.printFromHead();  // 输出: 30 <-> 20 <-> 10 <-> 40 <-> 50 <-> null

    // 删除头部节点
    list.removeAtHead();
    list.printFromHead();  // 输出: 20 <-> 10 <-> 40 <-> 50 <-> null

    // 删除尾部节点
    list.removeAtTail();
    list.printFromHead();  // 输出: 20 <-> 10 <-> 40 <-> null

    // 插入指定位置
    list.insertAtPosition(25, 1);
    list.printFromHead();  // 输出: 20 <-> 25 <-> 10 <-> 40 <-> null

    // 删除指定位置
    list.removeAtPosition(2);
    list.printFromHead();  // 输出: 20 <-> 25 <-> 40 <-> null

    return 0;
}
