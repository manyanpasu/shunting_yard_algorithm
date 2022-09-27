//
// Created by theta-sigma on 9/27/2022.
//

#include "ShuntingYard.h"

ShuntingYard::ShuntingYard() : infixExpression(), postfixExpression(),
                               digits("0123456789") {}

bool ShuntingYard::isNumber(const string &token) {
    bool flag;
    for (char character: token) {
        flag = false;
        for (int j = 0; j < strlen(digits) && !flag; j++) {
            if (character == digits[j]) {
                flag = true;
            }
        }

        if (!flag) {
            return false;
        }
    }

    return flag;
}

ShuntingYard::TokenType ShuntingYard::tokenTypeIdentifier(const string &token) {
    if (isNumber(token)) {
        return NUMBER;
    }

    if (token == "^") {
        return POW;
    }

    if (token == "*") {
        return MULTIPLICATION;
    }

    if (token == "/") {
        return DIVISION;
    }

    if (token == "+") {
        return PLUS;
    }

    if (token == "-") {
        return MINUS;
    }

    if (token == "sin") {
        return SIN;
    }

    if (token == "cos") {
        return COS;
    }

    if (token == ",") {
        return COMMA;
    }

    if (token == "(") {
        return LEFT_PARENTHESES;
    }

    if (token == ")") {
        return RIGHT_PARENTHESES;
    }

    return BAD_TOKEN;
}

ShuntingYard::TokenCategory ShuntingYard::tokenCategoryIdentifier(ShuntingYard::TokenType tt) {
    switch (tt) {
        case NUMBER:
            return NUMBER_CAT;
        case POW:
        case MULTIPLICATION:
        case DIVISION:
        case PLUS:
        case MINUS:
            return OPERATOR;
        case SIN:
        case COS:
            return FUNCTION;
        case COMMA:
            return SEPARATOR;
        case LEFT_PARENTHESES:
            return LEFT_PARENTHESES_CAT;
        case RIGHT_PARENTHESES:
            return RIGHT_PARENTHESES_CAT;
        case BAD_TOKEN:
        case UNKNOWN:
            return UNKNOWN_CAT;
    }
}

ShuntingYard::TokenPriority ShuntingYard::tokenPriorityIdentifier(ShuntingYard::TokenType tt) {
    switch (tt) {
        case POW:
            return FIRST;
        case MULTIPLICATION:
        case DIVISION:
            return SECOND;
        case PLUS:
        case MINUS:
            return THIRD;
        case NUMBER:
        case SIN:
        case COS:
        case COMMA:
        case LEFT_PARENTHESES:
        case RIGHT_PARENTHESES:
        case BAD_TOKEN:
        case UNKNOWN:
            return UNKNOWN_PRIORITY;
    }
}

ShuntingYard::TokenAssociativity ShuntingYard::tokenAssociativityIdentifier(ShuntingYard::TokenType tt) {
    switch (tt) {
        case POW:
            return RIGHT;
        case MULTIPLICATION:
        case DIVISION:
        case PLUS:
        case MINUS:
            return LEFT;
        case NUMBER:
        case SIN:
        case COS:
        case COMMA:
        case LEFT_PARENTHESES:
        case RIGHT_PARENTHESES:
        case BAD_TOKEN:
        case UNKNOWN:
            return UNKNOWN_ASSOCIATIVITY;
    }
}

void ShuntingYard::convert() {
    std::istringstream ss(rawInfixExpression);
    string token;
    postfixExpression = "";
    infixExpression = "";
    error = UNKNOWN_ERROR;
    tokensStack.makeEmpty();
    while (ss >> token) {
        infixExpression += token + " ";
        TokenType tokenType = tokenTypeIdentifier(token);

        if (tokenType == BAD_TOKEN) {
            error = BAD_TOKEN_ERROR;
            postfixExpression = getErrorMessage();
//                std::cout << postfixExpression << std::endl;
            return;
        }

        auto currentPair =
                std::pair<string, TokenType>({token, tokenType});

        TokenCategory tokenCat = tokenCategoryIdentifier(tokenType);
        if (tokenCat == NUMBER_CAT) {
            postfixExpression += token += " ";
            continue;
        }

        if (tokenCat == FUNCTION) {
            tokensStack.push(currentPair);
            continue;
        }

        if (tokenCat == SEPARATOR) {
            while (!tokensStack.isEmpty()) {
                const auto &topToken = std::get<string>(*tokensStack.peakAddress());
                TokenType topType = std::get<TokenType>(*tokensStack.peakAddress());
                if (topType != LEFT_PARENTHESES) {
                    postfixExpression += topToken + " ";
                    tokensStack.pop();
                } else {
                    break;
                }
            }
            if (tokensStack.isEmpty()) {
                error = MISMATCHED_PARENTHESES_OR_MISSED_SEP_ERROR;
                postfixExpression = getErrorMessage();
//                    std::cout << postfixExpression << std::endl;
                return;
            }
            continue;
        }

        if (tokenCat == OPERATOR) {
            if (!tokensStack.isEmpty()) {
                auto top = tokensStack.peakAddress();
                auto topType = std::get<TokenType>(*top);
                auto topToken = std::get<string>(*top);

                while (tokenCategoryIdentifier(topType) == OPERATOR &&
                       (tokenPriorityIdentifier(topType) <= tokenPriorityIdentifier(tokenType)) &&
                       (tokenPriorityIdentifier(topType) != tokenPriorityIdentifier(tokenType) ||
                        tokenAssociativityIdentifier(tokenType) != RIGHT)) {
                    postfixExpression += topToken + " ";
                    tokensStack.pop();

                    top = tokensStack.peakAddress();
                    topType = std::get<TokenType>(*top);
                    topToken = std::get<string>(*top);
                }
            }

            tokensStack.push(currentPair);
            continue;
        }

        if (tokenCat == LEFT_PARENTHESES_CAT) {
            tokensStack.push(std::pair<string, TokenType>({token, tokenType}));
            continue;
        }

        if (tokenCat == RIGHT_PARENTHESES_CAT) {
            string topToken;
            TokenType topType = UNKNOWN;

            while (topType != LEFT_PARENTHESES) {
                if (!tokensStack.isEmpty()) {
                    topToken = std::get<string>(*tokensStack.peakAddress());
                    topType = std::get<TokenType>(*tokensStack.peakAddress());
                } else {
                    error = MISMATCHED_PARENTHESES_ERROR;
                    postfixExpression = getErrorMessage();
//                        std::cout << postfixExpression << std::endl;
                    return;
                }
                if (tokenCategoryIdentifier(topType) == OPERATOR) {
                    postfixExpression += topToken += " ";
                    tokensStack.pop();
                }
            }

            if (tokenTypeIdentifier(topToken) == LEFT_PARENTHESES) {
                tokensStack.pop();
                if (!tokensStack.isEmpty()) {
                    topToken = std::get<string>(*tokensStack.peakAddress());
                    topType = std::get<TokenType>(*tokensStack.peakAddress());
                }
            }

            if (tokenCategoryIdentifier(topType) == FUNCTION) {
                postfixExpression += topToken += " ";
                tokensStack.pop();
                continue;
            }
        }
    }

    while (!tokensStack.isEmpty()) {
        string topToken = std::get<string>(*tokensStack.peakAddress());

        if (tokenTypeIdentifier(topToken) == RIGHT_PARENTHESES) {
            error = MISMATCHED_PARENTHESES_ERROR;
            postfixExpression = getErrorMessage();
//                std::cout << postfixExpression << std::endl;
            return;
        }

        postfixExpression += topToken += " ";
        tokensStack.pop();
    }

    error = NO_ERROR;
}

const string &ShuntingYard::getRawInfixExpression() const {
    return rawInfixExpression;
}

const string &ShuntingYard::getInfixExpression() const {
    return infixExpression;
}

const string &ShuntingYard::getPostfixExpression() const {
    return postfixExpression;
}

const char *ShuntingYard::getErrorMessage() const {
    switch (error) {
        case NO_ERROR:
            return "NO_ERROR";
        case BAD_TOKEN_ERROR:
            return "BAD_TOKEN_ERROR";
        case MISMATCHED_PARENTHESES_ERROR:
            return "MISMATCHED_PARENTHESES_ERROR";
        case MISMATCHED_PARENTHESES_OR_MISSED_SEP_ERROR:
            return "MISMATCHED_PARENTHESES_OR_MISSED_SEP_ERROR";
        case UNKNOWN_ERROR:
            return "UNKNOWN_ERROR";
    }
}
