#ifndef LAB4_RULE_H
#define LAB4_RULE_H

#include <string>

struct Rule{
    std::string currentState;
    char readSymbol;
    char writeSymbol;
    char move;
    std::string nextState;

    Rule() : currentState(""), readSymbol('\0'), writeSymbol('\0'), move('N'), nextState("") {}

    Rule(
            std::string currentState,
            char readSymbol,
            char writeSymbol,
            char move,
            std::string nextState
    ){
        this->currentState = currentState;
        this->readSymbol = readSymbol;
        this->writeSymbol = writeSymbol;
        this->move = move;
        this->nextState = nextState;
    }
};

#endif //LAB4_RULE_H