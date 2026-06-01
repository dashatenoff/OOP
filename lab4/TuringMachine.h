#ifndef LAB4_TURINGMACHINE_H
#define LAB4_TURINGMACHINE_H

#include <string>
#include <stdexcept>

#include "Tape.h"
#include "Rule.h"
#include "Sequence.h"

class TuringMachine{
protected:
    Tape<char>* tape;
    Sequence<Rule>* rules;
    std::string currentState;
    std::string haltState;

public:
    TuringMachine(
            Tape<char>* tape,
            Sequence<Rule>* rules,
            std::string startState = "q0",
            std::string haltState = "halt") {

        this->tape = tape;
        this->rules = rules;
        this->currentState = startState;
        this->haltState = haltState;
    }
        Rule FindRule(){
            char currentSymbol = tape->Read();
            for(int i = 0; i < rules->GetLength().GetValue(); i++){

                Rule rule = rules->Get(i);

                if(
                        rule.currentState == currentState &&
                        rule.readSymbol == currentSymbol
                        )
                {
                    return rule;
                }
            }

            throw std::logic_error(
                    "Rule not found"
            );
        }

        void Step(){

            Rule rule = FindRule();

            tape->Write(rule.writeSymbol);

            if(rule.move == 'L'){
                tape->MoveLeft();
            }
            else if(rule.move == 'R'){
                tape->MoveRight();
            }

            currentState = rule.nextState;
        }

        void Run(){
            while(currentState != haltState){
                Step();
            }
        }

        bool IsHalt() const{
            return currentState == haltState;
        }

        std::string GetCurrentState() const{
            return currentState;
        }

        Tape<char>* GetTape() const{
            return tape;
        }


    };




#endif //LAB4_TURINGMACHINE_H
