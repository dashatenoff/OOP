#include <iostream>
#include "Vector.h"
#include "test.h"

using namespace std;

void PrintMenu(){
    cout << "\n===== VECTOR MENU =====\n";
    cout << "1  PushBack\n";
    cout << "2  PushFront\n";
    cout << "3  InsertAt\n";
    cout << "4  PopBack\n";
    cout << "5  Set\n";
    cout << "6  Print\n";
    cout << "7  Vector + Vector\n";
    cout << "8  Multiply by scalar\n";
    cout << "9  Dot product\n";
    cout << "10 Norm\n";
    cout << "11 Map (+1)\n";
    cout << "12 Where (even)\n";
    cout << "13 Reduce (sum)\n";
    cout << "14 Range\n";
    cout << "15 PrimeNumbers\n";
    cout << "16 Run tests\n";
    cout << "0  Exit\n";
}

int plus1(int);
bool isEven(int);
int sum(int,int);

int main(){

    Vector<int> v;

    int cmd;

    while(true){

        PrintMenu();
        cout << "Command: ";
        cin >> cmd;

        if(cmd == 0)
            break;

        if(cmd == 1){
            int x;
            cout << "Value: ";
            cin >> x;

            v.PushBack(x);
        }

        if(cmd == 2){
            int x;
            cout << "Value: ";
            cin >> x;

            v.PushFront(x);
        }

        if(cmd == 3){
            int x,i;

            cout << "Value: ";
            cin >> x;

            cout << "Index: ";
            cin >> i;

            v.InsertAt(x,i);
        }

        if(cmd == 4){
            v.PopBack();
        }

        if(cmd == 5){
            int i,x;

            cout << "Index: ";
            cin >> i;

            cout << "Value: ";
            cin >> x;

            v.Set(i,x);
        }

        if(cmd == 6){
            cout << v << endl;
        }

        if(cmd == 7){

            Vector<int> other;

            int n;
            cout << "Size of second vector: ";
            cin >> n;

            for(int i=0;i<n;i++){
                int x;
                cin >> x;
                other.PushBack(x);
            }

            Vector<int> r = v + other;

            cout << "Result: " << r << endl;
        }

        if(cmd == 8){
            int k;

            cout << "Scalar: ";
            cin >> k;

            Vector<int> r = v * k;

            cout << r << endl;
        }

        if(cmd == 9){

            Vector<int> other;

            int n;
            cout << "Size of second vector: ";
            cin >> n;

            for(int i=0;i<n;i++){
                int x;
                cin >> x;
                other.PushBack(x);
            }

            cout << "Dot: " << v.Dot(other) << endl;
        }

        if(cmd == 10){
            cout << "Norm: " << v.Norm() << endl;
        }

        if(cmd == 11){
            Vector<int>* r = v.Map(plus1);

            cout << *r << endl;

            delete r;
        }

        if(cmd == 12){
            Vector<int>* r = v.Where(isEven);

            cout << *r << endl;

            delete r;
        }

        if(cmd == 13){
            int r = v.Reduce(sum,0);

            cout << "Reduce: " << r << endl;
        }

        if(cmd == 14){
            int l,r;

            cout << "l r: ";
            cin >> l >> r;

            Vector<int>* v2 = Vector<int>::Range(l,r);

            cout << *v2 << endl;

            delete v2;
        }

        if(cmd == 15){
            int l,r;

            cout << "l r: ";
            cin >> l >> r;

            Vector<int>* v2 = Vector<int>::PrimeNumbers(l,r);

            cout << *v2 << endl;

            delete v2;
        }

        if(cmd == 16){
            RunAllTests();
        }
    }

    return 0;
}