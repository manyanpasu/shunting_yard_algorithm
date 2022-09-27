#include <iostream>

#include "LinkedList.h"
#include "ArrayList.h"
#include "ShuntingYard.h"

#include <iomanip>

int main() {
    std::cout << "Hello, World!" << std::endl;
    {
        LinkedList<int> testList;

        std::cout << "LINKED LIST METHOD DEMONSTRATION" << std::endl << std::endl;

        for (int i = 0; i < 3; i++) {
            int x = i + 1;
            testList.insert(i, x);
            std::cout << "ll.insert(index: " << i << ", " << "x: " << x << ")\n";
            std::cout << "ll.getElementCopy(index: " << i << ") -> " <<
                      testList.getElementCopy(i) << "\n";
            std::cout << "*ll.getElementAddress(index: " << i << ") -> " <<
                      *testList.getElementAddress(i) << "\n";

            std::cout << std::endl << std::endl;
        }

        std::cout << std::endl;
        std::cout << "And all together with for-loop with i < ll.size() and \n"
                     "ll.getElementCopy(index)" << std::endl;
        for (int i = 0; i < testList.size(); i++) {
            std::cout << testList.getElementCopy(i) << " ";
        }

        std::cout << std::endl;
        std::cout << "And all together with for-loop with i < ll.size() and \n"
                     "ll.getElementAddress(index)" << std::endl;
        for (int i = 0; i < testList.size(); i++) {
            std::cout << *testList.getElementAddress(i) << " ";
        }

        std::cout << std::endl;
        for (int i = 0; i < 3; i++) {
            int x = (i + 1) * 10;
            testList.insert(i, x);
            std::cout << "ll.insert(index: " << i << ", " << "x: " << x << ")\n";
            std::cout << "ll.getElementCopy(index: " << i << ") -> " <<
                      testList.getElementCopy(i) << "\n";
            std::cout << "*ll.getElementAddress(index: " << i << ") -> " <<
                      *testList.getElementAddress(i) << "\n";

            std::cout << std::endl << std::endl;
        }

        std::cout << std::endl;
        std::cout << "And all together with for-loop with i < ll.size() and \n"
                     "ll.getElementCopy(index)" << std::endl;
        for (int i = 0; i < testList.size(); i++) {
            std::cout << testList.getElementCopy(i) << " ";
        }

        std::cout << std::endl;
        std::cout << "And all together with for-loop with i < ll.size() and \n"
                     "ll.getElementAddress(index)" << std::endl;
        for (int i = 0; i < testList.size(); i++) {
            auto eee = testList.getElementAddress(i);
            std::cout << *eee << " ";
        }

        std::cout << std::endl;
        std::cout << "ll.find(x: 2) -> ";
        int index = testList.find(2);
        std::cout << index << " ";

        std::cout << "ll.find(x: 10) -> ";
        index = testList.find(10);
        std::cout << index << " ";

        std::cout << "ll.find(x: 3) -> ";
        index = testList.find(3);
        std::cout << index << " ";

        std::cout << "ll.find(x: 1) -> ";
        index = testList.find(1);
        std::cout << index << " ";

        std::cout << "ll.find(x: 100) -> ";
        index = testList.find(100);
        std::cout << index << " ";

        std::cout << std::endl;
        testList.remove(4);

        std::cout << std::endl;
        for (int i = 0; i < testList.size(); i++) {
            std::cout << *testList.getElementAddress(i) << " ";
        }

        testList.remove(0);

        std::cout << std::endl;
        for (int i = 0; i < testList.size(); i++) {
            std::cout << testList.getElementCopy(i) << " ";
        }

        testList.remove(3);

        std::cout << std::endl;
        for (int i = 0; i < testList.size(); i++) {
            std::cout << testList.getElementCopy(i) << " ";
        }

        testList.remove(2);

        std::cout << std::endl;
        for (int i = 0; i < testList.size(); i++) {
            std::cout << testList.getElementCopy(i) << " ";
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

    ArrayList<string> ti;
    ti.append("( 1 + 2 ) )");
    ti.append("( 2 - 3 + 4 ) * ( 5 + 6 * 7 )");
    ti.append("3 + 4 * 2 / ( 1 - 5 ) ^ 2 ^ 3");
    ti.append("sin ( cos ( 2 , 3 ) / 3 * 314 )");
    ti.append("sin ( cos ( 2, 3 ) / 3 * 314 )");
    ti.append("( 1 + 2 ) )");


    ArrayList<string> to;
    to.append("MISMATCHED_PARENTHESES_ERROR");
    to.append("2 3 - 4 + 5 6 7 * + * ");
    to.append("3 4 2 * 1 5 - 2 3 ^ ^ / + ");
    to.append("2 3 cos 3 / 314 * sin ");
    to.append("BAD_TOKEN_ERROR");
    to.append("MISMATCHED_PARENTHESES_ERROR");


    ShuntingYard sy;

    string line;

    for (int i = 0; i < ti.size() && i < to.size(); i++) {
        sy.setRawInfixExpression(ti.get(i));
        sy.convert();
        string rpn = sy.getPostfixExpression();
        if (rpn == *to.getAdress(i)) {
            std::cout << i << ": correct!" << std::endl;
        } else {
            std::cout << i << ": incorrect!" << std::endl;
            std::cout << *ti.getAdress(i) << std::endl;
            std::cout << *to.getAdress(i) << std::endl;
            std::cout << rpn << std::endl;
        }
    }
//    if (std::getline(std::cin, line)) {
//        sy.setRawInfixExpression(line);
//        sy.convert();
//        string rie = sy.getRawInfixExpression();
//        string ie = sy.getInfixExpression();
//        string rpn = sy.getPostfixExpression();
//        auto syErrorMessage = sy.getErrorMessage();
//
//        std::cout << std::setw(20) << "your input: " << rie << std::endl;
//        std::cout << std::setw(20) << "infix expression: " << ie << std::endl;
//        std::cout << std::setw(20) << "postfix expression: " << rpn << std::endl;
//        std::cout << std::setw(20) << "error message: " << syErrorMessage << std::endl;
//    } else {
//        std::cout << "something wrong with input" << std::endl;
//    }

    return 0;
}
