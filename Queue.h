//
// Created by theta-sigma on 9/26/2022.
//

#ifndef ALGORITHMS_LAB1_QUEUE_H
#define ALGORITHMS_LAB1_QUEUE_H

#include <string>
#include <iostream>
#include "ArrayList.h"
#include "LinkedList.h"

// pop (снятие со стека),
// push (добавление на стек),
// peak (значение вершины стека без его снятия)

template<typename T>
class Queue {
private:
    LinkedList<T> ll;
public:
    Queue() = default;
/*
    void print() {
        for(int pBegin )
        std::cout <<
    }*/

    // push ->[0][1][2]-> pop
    T pop() {
        T value = ll.get(ll.size() - 1);
        ll.remove(ll.size() - 1);
        return value;
    }

    void push(T value) {
        ll.add(0, value);
    }

    // ->[][][X]->
    T peak() {
        return ll.get(ll.size() - 1);
    }
};

#endif //ALGORITHMS_LAB1_QUEUE_H
