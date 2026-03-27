#include <iostream>
#include "DynamicArray.h"
#include "LinkedList.h"
#include "MutableArraySequence.h"
#include "MutableListSequence.h"
#include "test.h"

using namespace std;

int plus1(int x) { return x + 1; }
bool isEven(int x) { return x % 2 == 0; }
int sum(int a, int b) { return a + b; }

void printSequence(Sequence<int>* seq){
    for (int i = 0; i < seq->GetLength(); i++){
        cout << seq->Get(i) << " ";
    }
    cout << "\n";
}

Sequence<int>* createArraySeq(){
    int n;
    cout << "Size: ";
    cin >> n;
    int* arr = new int[n];

    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    return new MutableArraySequence<int>(new DynamicArray<int>(arr, n));
}

Sequence<int>* createListSeq() {
    int n;
    cout << "Size: ";
    cin >> n;

    int* arr = new int[n];

    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    return new MutableListSequence<int>(new LinkedList<int>(arr, n));
}

int main() {
    int type;

    while (true) {
        cout << "\n1. ArraySequence\n2. ListSequence\n0. Exit\n";
        cin >> type;

        if (type == 0) break;

        Sequence<int>* seq = nullptr;

        if (type == 1) seq = createArraySeq();
        if (type == 2) seq = createListSeq();

        int cmd;

        while (true) {
            cout << "\n1. Print\n2. Append\n3. Map(+1)\n4. Where(even)\n5. Reduce(sum)\n6. Run tests\n0. Back\n";
            cin >> cmd;

            if (cmd == 0) break;

            if (cmd == 1) {
                printSequence(seq);
            }

            else if (cmd == 2) {
                int x;
                cout << "Value: ";
                cin >> x;
                seq->Append(x);
            }

            else if (cmd == 3) {
                Sequence<int>* res = seq->Map(plus1);
                printSequence(res);
                delete res;
            }

            else if (cmd == 4) {
                Sequence<int>* res = seq->Where(isEven);
                printSequence(res);
                delete res;
            }

            else if (cmd == 5) {
                int r = seq->Reduce(sum, 0);
                cout << "Result: " << r << "\n";
            }

            else if(cmd == 6)
            {
                RunAllTests();
            }
        }

        delete seq;
    }

    return 0;
}
