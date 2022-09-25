//
// Created by theta-sigma on 9/24/2022.
//

#ifndef ALGORITHMS_LAB1_LIST_H
#define ALGORITHMS_LAB1_LIST_H

template<typename T>
class List {
private:
    virtual void add(int index, T data) = 0;

    virtual T remove(int index) = 0;

    virtual T get(int index) = 0;

    virtual int size() = 0;
};

#endif //ALGORITHMS_LAB1_LIST_H
