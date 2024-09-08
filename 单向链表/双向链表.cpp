#include <iostream>

// �ڵ�ṹ
class DoublyLinkedListNode {
public:
    int data;  // �ڵ�����
    DoublyLinkedListNode* prev;  // ָ��ǰһ���ڵ�
    DoublyLinkedListNode* next;  // ָ����һ���ڵ�

    DoublyLinkedListNode(int value) : data(value), prev(nullptr), next(nullptr) {}
};

// ˫��������
class DoublyLinkedList {
private:
    DoublyLinkedListNode* head;  // ͷ�ڵ�
    DoublyLinkedListNode* tail;  // β�ڵ�
    int length;

public:
    // ���캯������ʼ��������
    DoublyLinkedList() : head(nullptr), tail(nullptr), length(0) {}

    // �����������ͷ������ڴ�
    ~DoublyLinkedList() {
        clear();
    }

    // ��ȡ������
    int getLength() const {
        return length;
    }

    // �ж������Ƿ�Ϊ��
    bool isEmpty() const {
        return length == 0;
    }

    // �������
    void clear() {
        DoublyLinkedListNode* current = head;
        while (current != nullptr) {
            DoublyLinkedListNode* nextNode = current->next;
            delete current;  // �ͷŵ�ǰ�ڵ���ڴ�
            current = nextNode;
        }
        head = nullptr;
        tail = nullptr;
        length = 0;
    }

    // ������ͷ������ڵ�
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

    // ������β������ڵ�
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

    // ��ָ��λ�ò���ڵ�
    void insertAtPosition(int value, int pos) {
        if (pos < 0 || pos > length) {
            std::cout << "λ����Ч" << std::endl;
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

    // ɾ������ͷ���ڵ�
    void removeAtHead() {
        if (isEmpty()) {
            std::cout << "����Ϊ�գ��޷�ɾ��" << std::endl;
            return;
        }

        DoublyLinkedListNode* deleteNode = head;
        if (head == tail) {  // ֻ��һ���ڵ�����
            head = tail = nullptr;
        } else {
            head = head->next;
            head->prev = nullptr;
        }
        delete deleteNode;
        length--;
    }

    // ɾ������β���ڵ�
    void removeAtTail() {
        if (isEmpty()) {
            std::cout << "����Ϊ�գ��޷�ɾ��" << std::endl;
            return;
        }

        DoublyLinkedListNode* deleteNode = tail;
        if (head == tail) {  // ֻ��һ���ڵ�����
            head = tail = nullptr;
        } else {
            tail = tail->prev;
            tail->next = nullptr;
        }
        delete deleteNode;
        length--;
    }

    // ɾ��ָ��λ�õĽڵ�
    void removeAtPosition(int pos) {
        if (pos < 0 || pos >= length) {
            std::cout << "λ����Ч" << std::endl;
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

    // ��ͷ��������ӡ����
    void printFromHead() const {
        DoublyLinkedListNode* current = head;
        while (current != nullptr) {
            std::cout << current->data << " <-> ";
            current = current->next;
        }
        std::cout << "null" << std::endl;
    }

    // ��β��������ӡ����
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

    // ��ͷ������ڵ�
    list.insertAtHead(10);
    list.insertAtHead(20);
    list.insertAtHead(30);
    list.printFromHead();  // ���: 30 <-> 20 <-> 10 <-> null

    // ��β������ڵ�
    list.insertAtTail(40);
    list.insertAtTail(50);
    list.printFromHead();  // ���: 30 <-> 20 <-> 10 <-> 40 <-> 50 <-> null

    // ɾ��ͷ���ڵ�
    list.removeAtHead();
    list.printFromHead();  // ���: 20 <-> 10 <-> 40 <-> 50 <-> null

    // ɾ��β���ڵ�
    list.removeAtTail();
    list.printFromHead();  // ���: 20 <-> 10 <-> 40 <-> null

    // ����ָ��λ��
    list.insertAtPosition(25, 1);
    list.printFromHead();  // ���: 20 <-> 25 <-> 10 <-> 40 <-> null

    // ɾ��ָ��λ��
    list.removeAtPosition(2);
    list.printFromHead();  // ���: 20 <-> 25 <-> 40 <-> null

    return 0;
}
