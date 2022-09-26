//
// Created by theta-sigma on 9/26/2022.
//

#ifndef ALGORITHMS_LAB1_STACK_H
#define ALGORITHMS_LAB1_STACK_H

#include "ArrayList.h"

// pop (снятие со стека),
// push (добавление на стек),
// peak (значение вершины стека без его снятия)

template<typename T>
class Stack {
private:
    ArrayList<T> ar;
public:
    Stack() = default;

    T pop() {
        if (ar.size() != 0) {
            int lastIndex = ar.size() - 1;
            T value = ar.get(lastIndex);
            ar.remove(lastIndex);
            return value;
        } else {
            return T();
        }
    }

    void push(T value) {
        int index = ar.size();
        ar.add(index, value);
    }

    T peak() {
        if (ar.size() != 0) {
            int lastIndex = ar.size() - 1;
            T value = ar.get(lastIndex);
            return value;
        } else {
            return T();
        }
    }

    bool isEmpty() {
        return ar.size() == 0;
    }
};


#endif //ALGORITHMS_LAB1_STACK_H
