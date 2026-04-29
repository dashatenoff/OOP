#include <iostream>
#include "Vector.h"
#include "test.h"

using namespace std;

void PrintMenu(){
    cout << "\n===== VECTOR MENU =====\n";
    cout << "1  PushBack\n";
    cout << "2  Set\n";
    cout << "3  Print\n";
    cout << "4  Vector + Vector\n";
    cout << "5  Multiply by scalar\n";
    cout << "6  Dot product\n";
    cout << "7 Norm\n";
    cout << "8 Map (+1)\n";
    cout << "9 Where (even)\n";
    cout << "10 Reduce (sum)\n";
    cout << "11 Range\n";
    cout << "12 PrimeNumbers\n";
    cout << "13 Run tests\n";
    cout << "0  Exit\n";
}

int plus1(const int&);
bool isEven(const int&);
int sum(const int&, const int&);

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
            int i,x;

            cout << "Index: ";
            cin >> i;

            cout << "Value: ";
            cin >> x;

            v.Set(i,x);
        }

        if(cmd == 3){
            cout << v << endl;
        }

        if(cmd == 4){

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

        if(cmd == 5){
            int k;

            cout << "Scalar: ";
            cin >> k;

            Vector<int> r = v * k;

            cout << r << endl;
        }

        if(cmd == 6){

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

        if(cmd == 7){
            cout << "Norm: " << v.Norm() << endl;
        }

        if(cmd == 8){
            Vector<int>* r = v.Map(plus1);

            cout << *r << endl;

            delete r;
        }

        if(cmd == 9){
            Vector<int>* r = v.Where(isEven);

            cout << *r << endl;

            delete r;
        }

        if(cmd == 10){
            int r = v.Reduce(sum,0);

            cout << "Reduce: " << r << endl;
        }

        if(cmd == 11){
            int l,r;

            cout << "l r: ";
            cin >> l >> r;

            Vector<int>* v2 = Vector<int>::Range(l,r);

            cout << *v2 << endl;

            delete v2;
        }

        if(cmd == 12){
            int l,r;

            cout << "l r: ";
            cin >> l >> r;

            Vector<int>* v2 = Vector<int>::PrimeNumbers(l,r);

            cout << *v2 << endl;

            delete v2;
        }

        if(cmd == 13){
            RunAllTests();
        }
    }

    return 0;
}