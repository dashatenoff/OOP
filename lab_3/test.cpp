#include <iostream>
#include <stdexcept>

#include "ImmutableArraySequence.h"
#include "Vector.h"
#include "Stack.h"
#include "Queue.h"

using namespace std;

static void PrintResult(const char* name, bool ok)
{
    cout << name << ": " << (ok ? "OK" : "FAIL") << endl;
}

static void PrintCheck(const char* name, int expected, int got)
{
    cout << name << endl;
    cout << "expected: " << expected << endl;
    cout << "got:      " << got << endl;
    cout << (expected == got ? "OK\n" : "FAIL\n") << endl;
}

int plus1(const int& x) { return x + 1; }
bool isEven(const int& x) { return x % 2 == 0; }
int sum(const int& a, const int& b) { return a + b; }

static void TestVector(){
    cout << "\n========== TestVector ==========\n";

    Vector<int> v;

    v.PushBack(1);
    v.PushBack(2);
    v.PushBack(3);

    PrintCheck("Size after PushBack", 3, v.Size());
    PrintCheck("Element [0]", 1, v[0]);
    PrintCheck("Element [1]", 2, v[1]);
    PrintCheck("Element [2]", 3, v[2]);

    v.Set(1,5);
    PrintCheck("Set index 1", 5, v[1]);
}

static void TestVectorAlgebra(){
    cout << "\n========== TestVectorAlgebra ==========\n";

    Vector<int> a;
    a.PushBack(1);
    a.PushBack(2);
    a.PushBack(3);

    Vector<int> b;
    b.PushBack(4);
    b.PushBack(5);
    b.PushBack(6);

    Vector<int> c = a + b;

    PrintCheck("Vector addition [0]",5,c[0]);
    PrintCheck("Vector addition [1]",7,c[1]);
    PrintCheck("Vector addition [2]",9,c[2]);

    Vector<int> d = a * 2;

    PrintCheck("Scalar multiplication [0]",2,d[0]);
    PrintCheck("Scalar multiplication [1]",4,d[1]);
    PrintCheck("Scalar multiplication [2]",6,d[2]);

    int dot = a.Dot(b);
    PrintCheck("Dot product",32,dot);

    double n = a.Norm();

    bool ok = (n > 3.7 && n < 3.75);
    PrintResult("Norm", ok);
}

static void TestVectorFunctional(){
    cout << "\n========== TestVectorFunctional ==========\n";

    Vector<int> v;

    v.PushBack(1);
    v.PushBack(2);
    v.PushBack(3);
    v.PushBack(4);

    Vector<int>* mapped = v.Map(plus1);
    Vector<int>* filtered = v.Where(isEven);
    int r = v.Reduce(sum,0);

    PrintCheck("Map [0]",2,(*mapped)[0]);
    PrintCheck("Map [1]",3,(*mapped)[1]);
    PrintCheck("Map [2]",4,(*mapped)[2]);
    PrintCheck("Map [3]",5,(*mapped)[3]);

    PrintCheck("Where size",2,filtered->Size());
    PrintCheck("Where [0]",2,(*filtered)[0]);
    PrintCheck("Where [1]",4,(*filtered)[1]);

    PrintCheck("Reduce result",10,r);

    delete mapped;
    delete filtered;
}

static void TestVectorEnumerator() {
    cout << "\n========== TestVectorEnumerator ==========\n";

    Vector<int> v;

    v.PushBack(1);
    v.PushBack(2);
    v.PushBack(3);

    IEnumerator<int>* it = v.GetEnumerator();

    int s = 0;

    while (it->MoveNext()) {
        s += it->Current();
    }

    PrintCheck("Enumerator sum",6,s);

    delete it;
}

static void TestVectorRangePrime() {
    cout << "\n========== TestVectorRangePrime ==========\n";

    Vector<int> *primes = Vector<int>::PrimeNumbers(1, 10);

    PrintCheck("PrimeNumbers size",4,primes->Size());
    PrintCheck("Prime[0]",2,(*primes)[0]);
    PrintCheck("Prime[1]",3,(*primes)[1]);
    PrintCheck("Prime[2]",5,(*primes)[2]);
    PrintCheck("Prime[3]",7,(*primes)[3]);

    delete primes;
}

static void TestVectorMutableImmutable(){
    cout << "\n========== TestVectorMutableImmutable ==========\n";

    int arr[] = {1,2,3};

    Vector<int> v(
            new ImmutableArraySequence<int>(
                    new DynamicArray<int>(arr,3)
            )
    );

    int oldSize = v.Size();

    v.PushBack(4);

    PrintCheck("Immutable append new size", oldSize + 1, v.Size());
}



static void TestVectorErrors()
{
    cout << "\n========== TestVectorErrors ==========\n";

    Vector<int> v;

    bool ok = false;

    try{
        v.Set(10,5);
    }
    catch(std::out_of_range&)
    {
        ok = true;
    }

    PrintResult("PopBack empty", ok);

    ok = false;

    try{
        v.Get(10);
    }
    catch(std::out_of_range&)
    {
        ok = true;
    }

    PrintResult("Get invalid index", ok);

    ok = false;

    try{
        int x = v[10];
    }
    catch(std::out_of_range&)
    {
        ok = true;
    }

    PrintResult("operator[] invalid index", ok);
}

static void TestStack(){

    cout << "\n========== TestStack ==========\n";

    Stack<int> s;

    s.Push(1);
    s.Push(2);
    s.Push(3);

    bool ok;

    ok = (s.Size() == 3);
    PrintResult("Push + Size", ok);

    ok = (s.Top() == 3);
    PrintResult("Top", ok);

    int x = s.Pop();

    ok = (x == 3 && s.Size() == 2);
    PrintResult("Pop", ok);
}

static void TestStackFunctional(){

    cout << "\n========== TestStackFunctional ==========\n";

    Stack<int> s;

    s.Push(1);
    s.Push(2);
    s.Push(3);
    s.Push(4);

    Stack<int>* mapped = s.Map(plus1);
    Stack<int>* filtered = s.Where(isEven);

    bool ok;

    ok = (mapped->Top() == 5);
    PrintResult("Stack Map", ok);

    ok = (filtered->Size() == 2 &&
          filtered->Top() == 4);

    PrintResult("Stack Where", ok);

    delete mapped;
    delete filtered;
}

static void TestStackFindSubsequence(){

    cout << "\n========== TestStackFindSubsequence ==========\n";

    Stack<int> s;

    s.Push(1);
    s.Push(2);
    s.Push(3);
    s.Push(4);
    s.Push(5);

    Stack<int> sub;

    sub.Push(3);
    sub.Push(4);

    int index = s.FindSubsequence(sub);

    bool ok = (index == 2);

    PrintResult("FindSubsequence", ok);
}

static void TestQueue(){
    cout << "\n========== TestQueue ==========\n";

    Queue<int>* que = new Queue<int>();;

    que->Enqueue(1);
    que->Enqueue(2);
    que->Enqueue(3);

    bool ok;

    ok = (que->Size() == 3);
    PrintResult("Size after Enqueue", ok);

    ok = (que->Front() == 1);
    PrintResult("Front element", ok);

    int v = que->Dequeue();
    ok = (v == 1);
    PrintResult("Dequeue returns first", ok);

    ok = (que->Size() == 2);
    PrintResult("Size after Dequeue", ok);

    ok = (que->Front() == 2);
    PrintResult("Front after Dequeue", ok);

    que->Dequeue();
    que->Dequeue();

    ok = (que->Empty());
    PrintResult("Empty queue", ok);

    delete que;
}

static void TestQueueSplit(){
    cout << "\n========== TestQueueSplit ==========\n";

    Queue<int> q;

    q.Enqueue(1);
    q.Enqueue(2);
    q.Enqueue(3);
    q.Enqueue(4);
    q.Enqueue(5);

    Queue<int> even;
    Queue<int> odd;

    q.Split(isEven, even, odd);

    bool ok;

    ok = (even.Size() == 2);
    PrintResult("Even size", ok);

    ok = (odd.Size() == 3);
    PrintResult("Odd size", ok);

    ok = (even.Front() == 2);
    PrintResult("Even first element", ok);

    ok = (odd.Front() == 1);
    PrintResult("Odd first element", ok);
}


void RunAllTests(){

    cout << "\n============================\n";
    cout << "RUNNING VECTOR TESTS\n";
    cout << "============================\n";

    TestVector();
    TestVectorAlgebra();
    TestVectorFunctional();
    TestVectorEnumerator();
    TestVectorRangePrime();
    TestVectorMutableImmutable();
    TestVectorErrors();
    TestStack();
    TestStackFunctional();
    TestStackFindSubsequence();
    TestQueue();
    TestQueueSplit();

    cout << "\nALL TESTS FINISHED\n";
}