//
// Created by theta-sigma on 9/26/2022.
//

#ifndef ALGORITHMS_LAB1_SHUNTINGYARD_H
#define ALGORITHMS_LAB1_SHUNTINGYARD_H

#include <string>
#include <cstring>
#include <stdexcept>
#include <iostream>

#include <string>
#include <sstream>
#include <algorithm>
#include "Queue.h"
#include "Stack.h"

using std::string;

class ShuntingYard {
public:
    string infixExpression;
    string postfixExpression;

    char firstPriorityOperations[1][2];
    char secondPriorityOperations[2][2];
    char thirdPriorityOperations[2][2];
    char functions[2][10];
    char separators[1][2];
    char digits[11];

    enum Tokens {
        NUMBER, RIGHT_OPERATION_1, OPERATION_2, OPERATION_3, SEPARATOR, FUNCTION, PARENTHESES, BADTOKEN
    };

    bool tokenTypeIdentifierStep(const string &token, Tokens tokenType) {
        char *ccc = nullptr;
        int nnn = 0;
        int mmm = 0;
//        int len = 0;
        switch (tokenType) {
            case RIGHT_OPERATION_1: {
                ccc = &firstPriorityOperations[0][0];
                nnn = sizeof(firstPriorityOperations) / sizeof(firstPriorityOperations[0]);
                mmm = sizeof(firstPriorityOperations[0]) / sizeof(char);
                break;
            }
            case OPERATION_2: {
                ccc = &secondPriorityOperations[0][0];
                nnn = sizeof(secondPriorityOperations) / sizeof(secondPriorityOperations[0]);
                mmm = sizeof(secondPriorityOperations[0]) / sizeof(char);
                break;
            }
            case OPERATION_3: {
                ccc = &thirdPriorityOperations[0][0];
                nnn = sizeof(thirdPriorityOperations) / sizeof(thirdPriorityOperations[0]);
                mmm = sizeof(thirdPriorityOperations[0]) / sizeof(char);
                break;
            }
            case SEPARATOR: {
                ccc = &separators[0][0];
                nnn = sizeof(separators) / sizeof(separators[0]);
                mmm = sizeof(separators[0]) / sizeof(char);
                break;
            }
            case FUNCTION: {
                ccc = &functions[0][0];
                nnn = sizeof(functions) / sizeof(functions[0]);
                mmm = sizeof(functions[0]) / sizeof(char);
                break;
            }
            case NUMBER:
            case BADTOKEN:
            case PARENTHESES:
                break;
        }

        for (int i = 0; i < nnn; i++) {
            if (strcmp(token.c_str(), &ccc[i * mmm]) == 0) {
                return true;
            }
        }
        return false;
    }

    Tokens tokenTypeIdentifier(const string &token) {
        // NUMBER
        bool isNumber;
        for (char character: token) {
            isNumber = false;
            for (int j = 0; j < strlen(digits) && !isNumber; j++) {
                if (character == digits[j]) {
                    isNumber = true;
                }
            }
            if (!isNumber) {
                break;
            }
        }

        if (isNumber) {
            return NUMBER;
        }

        if (token == "(" || token == ")") {
            return PARENTHESES;
        }

        // OTHER TOKENS
        Tokens otherTokens[] = {RIGHT_OPERATION_1, OPERATION_2, OPERATION_3, SEPARATOR, FUNCTION};
        for (Tokens ttt: otherTokens) {
            if (tokenTypeIdentifierStep(token, ttt)) {
                return ttt;
            }
        }

        return BADTOKEN;
    }

    ShuntingYard() : infixExpression(), postfixExpression(),
                     firstPriorityOperations{"^"},
                     secondPriorityOperations{"*", "/"},
                     thirdPriorityOperations{"+", "-"},
                     functions{"sin", "cos"},
                     separators{","},
                     digits("0123456789") {}

    ~ShuntingYard() = default;

    void convertFromInput() {
        string line;
        string outputQueue;
        Stack<std::pair<string, Tokens>> tokensStack;

        if (std::getline(std::cin, line)) {
            std::istringstream ss(line);
            string token;
            while (ss >> token) {
                std::cout << token << " ";
                Tokens tokenType = tokenTypeIdentifier(token);
                std::cout << tokenType << std::endl;

                if (tokenType == BADTOKEN) {
                    std::cout << "bad token: " << token << std::endl;
                    return;
                }

                std::pair<string, Tokens> currentPair = std::pair<string, Tokens>({token, tokenType});

                if (tokenType == NUMBER) {
                    outputQueue += token += " ";
                } else if (tokenType == FUNCTION) {
                    tokensStack.push(currentPair);
                } else if (tokenType == SEPARATOR) {
                    while (!tokensStack.isEmpty() && std::get<string>(tokensStack.peak()) != "(") {
                        outputQueue += std::get<string>(tokensStack.pop()) += " ";
                    }
                    if (tokensStack.isEmpty()) {
                        std::cout << "there are mismatched parentheses "
                                     "OR missed separator\n\n";
                        return;
                    }
                } else if (tokenType == RIGHT_OPERATION_1 ||
                           tokenType == OPERATION_2 ||
                           tokenType == OPERATION_3) {

                    auto top = tokensStack.peak();
                    Tokens topType = std::get<Tokens>(top);
                    while ((topType == RIGHT_OPERATION_1 ||
                            topType == OPERATION_2 ||
                            topType == OPERATION_3) && (topType <= tokenType)
                           && (topType != tokenType || tokenType != RIGHT_OPERATION_1)) {
                        outputQueue += (std::get<string>(top)) += " ";
                        tokensStack.pop();

                        top = tokensStack.peak();
                        topType = std::get<Tokens>(top);
                    }
                    tokensStack.push(currentPair);
                } else if (token == "(") {
                    tokensStack.push(std::pair<string, Tokens>({"(", PARENTHESES}));
                } else if (token == ")") {
                    string topToken;
                    Tokens topType;
                    if (!tokensStack.isEmpty()) {
                        topToken = std::get<string>(tokensStack.peak());
                        topType = std::get<Tokens>(tokensStack.peak());
                    } else {
                        std::cout << "there are mismatched parentheses\n\n";
                        return;
                    }
                    while (topToken != "(") {
                        if (topType == RIGHT_OPERATION_1 ||
                            topType == OPERATION_2 ||
                            topType == OPERATION_3) {

                            outputQueue += topToken += " ";
                            tokensStack.pop();

                            if (!tokensStack.isEmpty()) {
                                topToken = std::get<string>(tokensStack.peak());
                                topType = std::get<Tokens>(tokensStack.peak());
                            } else {
                                std::cout << "there are mismatched parentheses\n\n";
                                return;
                            }
                        }
                    }
                    if (topToken == "(") {
                        tokensStack.pop();
                        topToken = std::get<string>(tokensStack.peak());
                        topType = std::get<Tokens>(tokensStack.peak());
                    }

                    if (topType == FUNCTION) {
                        outputQueue += topToken += " ";
                        tokensStack.pop();
                    }
                }
            }

            while (!tokensStack.isEmpty()) {
                string topToken = std::get<string>(tokensStack.peak());
                //Tokens topType = std::get<Tokens>(tokensStack.peak());

                if (topToken == "(") {
                    std::cout << "there are mismatched parentheses\n\n";
                    return;
                }

                outputQueue += topToken += " ";
                tokensStack.pop();
            }
        }

        std::cout << outputQueue;
    }

//    void setInfixExpression(const string &expression) {
//        infixExpression = expression;
//    }

//    string getInfixExpression() const {
//        return infixExpression;
//    }

//    string getPostfixExpression() const {
//        return postfixExpression;
//    }

};


#endif //ALGORITHMS_LAB1_SHUNTINGYARD_H
