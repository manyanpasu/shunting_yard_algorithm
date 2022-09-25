//
// Created by theta-sigma on 9/25/2022.
//

#ifndef ALGORITHMS_LAB1_ARRAYLIST_H
#define ALGORITHMS_LAB1_ARRAYLIST_H

template<typename T>
class ArrayList {
private:
    T *array;
    int capacity;
    int mSize;

    void extend() {
        T *xxx = new T[capacity *= 2];
        for (int i = 0; i < mSize; i++) {
            xxx[i] = array[i];
        }

        delete[] array;
        array = xxx;
    }

public:
    ArrayList() {
        capacity = 3;
        array = new T[capacity];
        mSize = 0;
    }

    ~ArrayList() {
        delete[] array;
    }

    T get(int index) { // индекс всегда корректный
        return array[index];
    }

    T set(int index, T x) { // индекс всегда корректный
        array[index] = x;
        return array[index];
    }

    T add(int index, T x) { // под add имеется ввиду вставка
        if (mSize == capacity) {
            extend();
        }

        for (int i = mSize; i > index; i--) {
            array[i] = array[i - 1];
        }

        array[index] = x;
        mSize++;

        return array[index];
    }

    int find(T x) {
        for (int i = 0; i < mSize; i++) {
            if (array[i] == x) {
                return i;
            }
        }
        return -1;
    }

    void remove(int index) {
        for (int i = index; i < mSize - 1; i++) {
            array[i] = array[i + 1];
        }
        mSize--;
    }

    int size() {
        return mSize;
    }
};


#endif //ALGORITHMS_LAB1_ARRAYLIST_H
