#include <iostream>
#include "LazySequence.h"
#include "MutableArraySequence.h"
#include "DynamicArray.h"
#include "SequenceReadStream.h"
#include "SequenceWriteStream.h"
#include "TuringMachine.h"
#include "MutableListSequence.h"
#include "LinkedList.h"
#include "Tape.h"
#include "Rule.h"

void LazySequenceDemo(){

    std::cout << "1. Fibonacci\n";
    std::cout << "2. Manual sequence\n";

    int type;
    std::cin >> type;

    LazySequence<int>* seq;

    if(type == 1){

        std::function<int(Sequence<int>*)> fib = [](Sequence<int>* s) -> int {

            int len =s->GetLength().GetValue();

            if(len == 0){
                return 0;
            }

            if(len == 1){
                return 1;
            }

            return s->Get(len - 1)
                   + s->Get(len - 2);
        };

        seq = new LazySequence<int>(
                fib,
                new MutableArraySequence<int>(
                        new DynamicArray<int>(0)
                )
        );
    }

    if(type == 2){

        int n;

        std::cout << "Size:\n";
        std::cin >> n;

        int* arr = new int[n];

        for(int i = 0; i < n; i++){
            std::cin >> arr[i];
        }

        seq = new LazySequence<int>(
                arr,
                n
        );

        delete[] arr;
    }

    while(true){

        std::cout << "\n1. Get\n";
        std::cout << "2. Insert\n";
        std::cout << "3. Append\n";
        std::cout << "4. Print first 10\n";
        std::cout << "0. Exit\n";

        int cmd;
        std::cin >> cmd;

        if(cmd == 1){

            int index;

            std::cout << "Index:\n";
            std::cin >> index;

            std::cout
                    << seq->Get(index)
                    << std::endl;
        }

        if(cmd == 2){

            int value;
            int index;

            std::cout << "Value and index:\n";

            std::cin >> value >> index;

            seq->InsertAt(value,index);
        }

        if(cmd == 3){

            int value;

            std::cout << "Value:\n";

            std::cin >> value;

            seq->Append(value);
        }

        if(cmd == 4){

            for(int i = 0; i < 10; i++){

                std::cout
                        << seq->Get(i)
                        << " ";
            }

            std::cout << std::endl;
        }

        if(cmd == 0){
            break;
        }
    }

    delete seq;
}

void StreamDemo(){

    auto* seq =
            new MutableArraySequence<int>(
                    new DynamicArray<int>(0)
            );

    SequenceWriteStream<int> out(seq);

    SequenceReadStream<int> in(seq);

    out.Open();

    while(true){

        std::cout << "\n1. Write\n";
        std::cout << "2. Read all\n";
        std::cout << "3. Current write position\n";
        std::cout << "0. Exit\n";

        int cmd;
        std::cin >> cmd;

        if(cmd == 1){

            int value;

            std::cout << "Value:\n";
            std::cin >> value;

            out.Write(value);

            std::cout << "Written\n";
        }

        if(cmd == 2){

            in.Open();

            std::cout << "Sequence:\n";

            while(!in.IsEndOfStream()){
                std::cout << in.Read() << " ";
            }

            std::cout << std::endl;

            in.Close();

            in.Seek(0);
        }

        if(cmd == 3){

            std::cout
                    << out.GetPosition()
                    << std::endl;
        }

        if(cmd == 0){
            break;
        }
    }

    out.Close();

    delete seq;
}

void TuringDemo(){

    std::string input;

    std::cout << "Input tape (only 0 and 1): ";
    std::cin >> input;

    auto* list =
            new LinkedList<char>();

    for(int i = 0; i < input.size(); i++){
        list->Append(input[i]);
    }

    Tape<char>* tape =
            new Tape<char>(
                    new MutableListSequence<char>(list),
                    '_'
            );

    auto* rules =
            new MutableArraySequence<Rule>(
                    new DynamicArray<Rule>(0)
            );

    rules->Append(
            Rule(
                    "q0",
                    '1',
                    '0',
                    'R',
                    "q0"
            )
    );

    rules->Append(
            Rule(
                    "q0",
                    '0',
                    '0',
                    'R',
                    "q0"
            )
    );

    rules->Append(
            Rule(
                    "q0",
                    '_',
                    '_',
                    'R',
                    "halt"
            )
    );

    TuringMachine tm(
            tape,
            rules
    );

    std::cout << "\nBefore:\n";
    tape->Print();

    std::cout << "\nPress Enter to run...";
    std::cin.ignore();
    std::cin.get();

    tm.Run();

    std::cout << "\nAfter:\n";
    tape->Print();

    delete tape;
    delete rules;
}