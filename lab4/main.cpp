#include <iostream>

void LazySequenceDemo();
void StreamDemo();
void TuringDemo();
void RunAllTests();

int main(){

    while(true){

        std::cout << "\n1. LazySequence\n";
        std::cout << "2. Streams\n";
        std::cout << "3. Turing Machine\n";
        std::cout << "4. Tests\n";
        std::cout << "0. Exit\n";

        int choice;
        std::cin >> choice;

        if(choice == 1){
            LazySequenceDemo();
        }

        if(choice == 2){
            StreamDemo();
        }

        if(choice == 3){
            TuringDemo();
        }

        if(choice == 4){
            RunAllTests();
        }
        if(choice == 0){
            break;
        }
    }

    return 0;
}