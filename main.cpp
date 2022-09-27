#include <iostream>

#include "LinkedList.h"
#include "ArrayList.h"
#include "ShuntingYard.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    {
        LinkedList<int> testList;

        for (int i = 0; i < 3; i++) {
            int ret = testList.add(i, i + 1);
            std::cout << ret << " ";
        }

        for (int i = 0; i < testList.size(); i++) {
            std::cout << testList.get(i) << " ";
        }

        for (int i = 0; i < 3; i++) {
            testList.add(i, (i + 1) * 10);
        }

        std::cout << std::endl;
        for (int i = 0; i < testList.size(); i++) {
            std::cout << testList.get(i) << " ";
        }

        std::cout << std::endl;
        int index = testList.find(2);
        std::cout << index << " ";

        index = testList.find(10);
        std::cout << index << " ";

        index = testList.find(3);
        std::cout << index << " ";

        index = testList.find(1);
        std::cout << index << " ";

        index = testList.find(100);
        std::cout << index << " ";

        std::cout << std::endl;
        testList.remove(4);

        std::cout << std::endl;
        for (int i = 0; i < testList.size(); i++) {
            std::cout << testList.get(i) << " ";
        }

        testList.remove(0);

        std::cout << std::endl;
        for (int i = 0; i < testList.size(); i++) {
            std::cout << testList.get(i) << " ";
        }

        testList.remove(3);

        std::cout << std::endl;
        for (int i = 0; i < testList.size(); i++) {
            std::cout << testList.get(i) << " ";
        }

        testList.remove(2);

        std::cout << std::endl;
        for (int i = 0; i < testList.size(); i++) {
            std::cout << testList.get(i) << " ";
        }
    }
    /////
    {
        ArrayList<int> ll;

        for (int i = 0; i < 3; i++) {
            int ret = ll.add(i, i + 1);
            std::cout << ret << " ";
        }

        for (int i = 0; i < ll.size(); i++) {
            std::cout << ll.get(i) << " ";
        }

        for (int i = 0; i < 3; i++) {
            ll.add(i, (i + 1) * 10);
        }

        std::cout << std::endl;
        for (int i = 0; i < ll.size(); i++) {
            std::cout << ll.get(i) << " ";
        }

        std::cout << std::endl;
        int index = ll.find(2);
        std::cout << index << " ";

        index = ll.find(10);
        std::cout << index << " ";

        index = ll.find(3);
        std::cout << index << " ";

        index = ll.find(1);
        std::cout << index << " ";

        index = ll.find(100);
        std::cout << index << " ";

        std::cout << std::endl;
        ll.remove(4);

        std::cout << std::endl;
        for (int i = 0; i < ll.size(); i++) {
            std::cout << ll.get(i) << " ";
        }

        ll.remove(0);

        std::cout << std::endl;
        for (int i = 0; i < ll.size(); i++) {
            std::cout << ll.get(i) << " ";
        }

        ll.remove(3);

        std::cout << std::endl;
        for (int i = 0; i < ll.size(); i++) {
            std::cout << ll.get(i) << " ";
        }

        ll.remove(2);

        std::cout << std::endl;
        for (int i = 0; i < ll.size(); i++) {
            std::cout << ll.get(i) << " ";
        }
    }

    std::cout << "\n\n//////////////\n\n";

    ShuntingYard sy;

    // input: ( 2 - 3 + 4 ) * ( 5 + 6 * 7 )
    // output: 2 3 - 4 + 5 6 7 * + *

    // input:  3 + 4 * 2 / ( 1 − 5 ) ^ 2 ^ 3
    // output: 3 4 2 * 1 5 − 2 3 ^ ^ / +

    // input:  sin ( cos ( 2 , 3 ) / 3 * 314 )
    // output: 2 3 cos 3 / 314 * sin

    // input: sin ( cos ( 2, 3 ) / 3 * 314 )
    // output: bad token

    // / / sin ( cos ( 2 , 3 ) / 3 * 314 )
    // ???

    sy.convertFromInput();

    return 0;
}
