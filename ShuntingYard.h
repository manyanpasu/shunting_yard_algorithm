//
// Created by theta-sigma on 9/27/2022.
//

#ifndef ALGORITHMS_LAB1_SHUNTINGYARD_H
#define ALGORITHMS_LAB1_SHUNTINGYARD_H

#include <string>
#include <cstring>   // strlen
#include <iostream>  // std::cout, std::cin;
#include <algorithm> // std::getElementCopy<T>
#include <sstream>   // std::istringstream

#include "Stack.h"

using std::string;

class ShuntingYard {
public:
    ShuntingYard();

    ~ShuntingYard() = default;

    void setRawInfixExpression(const string &expression) {
        rawInfixExpression = expression;
    };

    void convert();

    const string &getRawInfixExpression() const;

    const string &getInfixExpression() const;

    const string &getPostfixExpression() const;

    const char *getErrorMessage() const;

private:
    enum TokenType {
        NUMBER,

        POW,

        MULTIPLICATION,
        DIVISION,

        PLUS,
        MINUS,

        SIN,
        COS,

        COMMA,

        LEFT_PARENTHESES,
        RIGHT_PARENTHESES,

        BAD_TOKEN,

        UNKNOWN
    };

    enum TokenCategory {
        NUMBER_CAT,
        OPERATOR,
        SEPARATOR,
        FUNCTION,
        LEFT_PARENTHESES_CAT,
        RIGHT_PARENTHESES_CAT,
        UNKNOWN_CAT
    };

    enum TokenPriority {
        FIRST,
        SECOND,
        THIRD,
        UNKNOWN_PRIORITY
    };

    enum TokenAssociativity {
        LEFT,
        RIGHT,
        UNKNOWN_ASSOCIATIVITY
    };

    enum errorType {
        NO_ERROR,
        BAD_TOKEN_ERROR,
        MISMATCHED_PARENTHESES_ERROR,
        MISMATCHED_PARENTHESES_OR_MISSED_SEP_ERROR,
        UNKNOWN_ERROR
    };

    errorType error;

    string rawInfixExpression;
    string infixExpression;
    string postfixExpression;
    Stack<std::pair<string, TokenType>> tokensStack;

    char digits[11];

    bool isNumber(const string &token);

    TokenType tokenTypeIdentifier(const string &token);

    static TokenCategory tokenCategoryIdentifier(TokenType tt);

    static TokenPriority tokenPriorityIdentifier(TokenType tt);

    static TokenAssociativity tokenAssociativityIdentifier(TokenType tt);
};


#endif //ALGORITHMS_LAB1_SHUNTINGYARD_H
