//
// Created by theta-sigma on 9/24/2022.
//

#ifndef ALGORITHMS_LAB1_LINKEDLIST_H
#define ALGORITHMS_LAB1_LINKEDLIST_H

template<typename T>
class LinkedList {
private:
    struct Node {
    public:
        explicit Node(T data) : data(data), next(nullptr) {};

        T data;
        Node *next;
    };

    int mSize;
    Node *head;
public:
    LinkedList<T>() {
        head = nullptr;
        mSize = 0;
    }

    ~LinkedList<T>() {
        Node *cur = head;
        for (int i = 0; i < mSize; i++) {
            Node *next = cur->next;
            delete cur;
            cur = next;
        }
    }

    T getElementCopy(int index) {
        Node *current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return current->data;
    }

    const T *getElementAddress(int index) {
        Node *current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return &(current->data);
    }

    void insert(int index, T x) { // под insert имеется ввиду вставка
        Node **current = &head;
        for (int i = 0; i < index; i++) {
            current = &((*current)->next);
        }
        Node *pNext = *current;
        *current = new Node(x);
        (*current)->next = pNext;

        mSize++;
    }

    int find(T x) {
        Node *current = head;
        for (int i = 0; current != nullptr; i++) {
            if (current->data == x) {
                return i;
            }
            current = current->next;
        }
        return -1;
    }

    void remove(int index) { // индекс всегда корректный
        if (index == 0) {
            Node *xxx = head->next;
            delete head;
            head = xxx;
        } else {
            Node *current = head;
            for (int i = 0; i < index - 1; i++) {
                current = current->next;
            }

            Node *xxx = current->next;
            current->next = current->next->next;
            delete xxx;
        }

        mSize--;
    }

    int size() {
        return mSize;
    }
};

#endif //ALGORITHMS_LAB1_LINKEDLIST_H
