#include <iostream>
#include <stdexcept>

#include "DynamicArray.h"
#include "LinkedList.h"

#include "MutableArraySequence.h"
#include "ImmutableArraySequence.h"

#include "MutableListSequence.h"
#include "ImmutableListSequence.h"

#include "Sequence.h"
#include "test.h"

#include "Vector.h"

using namespace std;

static void PrintResult(const char* name, bool ok)
{
    cout << name << ": " << (ok ? "OK" : "FAIL") << endl;
}
int plus1(int x) { return x + 1; }
bool isEven(int x) { return x % 2 == 0; }
int sum(int a, int b) { return a + b; }

static void TestVector(){
    cout << "\n========== TestVector ==========\n";

    bool ok;

    Vector<int> v;

    v.PushBack(1);
    v.PushBack(2);
    v.PushBack(3);

    ok = (v.Size() == 3 &&
          v[0] == 1 &&
          v[1] == 2 &&
          v[2] == 3);

    PrintResult("PushBack + operator[]", ok);

    v.PushFront(0);

    ok = (v[0] == 0);
    PrintResult("PushFront", ok);

    v.InsertAt(10,2);

    ok = (v[2] == 10);
    PrintResult("InsertAt", ok);

    v.PopBack();

    ok = (v.Size() == 4);
    PrintResult("PopBack", ok);

    v.Set(1,5);

    ok = (v[1] == 5);
    PrintResult("Set", ok);
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

    bool ok;

    ok = (c[0] == 5 && c[1] == 7 && c[2] == 9);
    PrintResult("Vector addition", ok);

    Vector<int> d = a * 2;

    ok = (d[0] == 2 && d[1] == 4 && d[2] == 6);
    PrintResult("Scalar multiplication", ok);

    int dot = a.Dot(b);

    ok = (dot == 32);
    PrintResult("Dot product", ok);

    double n = a.Norm();

    ok = (n > 3.7 && n < 3.75);
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

    bool ok;

    ok = ((*mapped)[0] == 2 &&
          (*mapped)[1] == 3 &&
          (*mapped)[2] == 4 &&
          (*mapped)[3] == 5);

    PrintResult("Vector Map", ok);

    ok = (filtered->Size() == 2 &&
          (*filtered)[0] == 2 &&
          (*filtered)[1] == 4);

    PrintResult("Vector Where", ok);

    ok = (r == 10);
    PrintResult("Vector Reduce", ok);

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

    bool ok = (s == 6);

    PrintResult("Vector Enumerator", ok);

    delete it;
}

static void TestVectorRangePrime() {
    cout << "\n========== TestVectorRangePrime ==========\n";

    Vector<int> *primes = Vector<int>::PrimeNumbers(1, 10);

    bool ok =
            (primes->Size() == 4 &&
             (*primes)[0] == 2 &&
             (*primes)[1] == 3 &&
             (*primes)[2] == 5 &&
             (*primes)[3] == 7);

    PrintResult("Range + PrimeNumbers", ok);

    delete primes;
}

static void TestVectorMutableImmutable(){
    cout << "\n========== TestVectorMutableImmutable ==========\n";

    bool ok;
    int arr[] = {1,2, 3};

    Vector<int> v = new ImmutableArraySequence<int>(new DynamicArray<int>(arr,3));

    int oldSize = v.Size();

    v.PushBack(4);

    ok = (v.Size() == oldSize + 1);

    PrintResult("Immutable append returns new sequence", ok);
}

static void TestVectorErrors()
{
    cout << "\n========== TestVectorErrors ==========\n";

    Vector<int> v;

    bool ok = false;

    try{
        v.PopBack();
    }
    catch(std::out_of_range&)
    {
        ok = true;
    }

    assert(ok);

    PrintResult("PopBack empty", ok);


    ok = false;

    try{
        v.Get(10);
    }
    catch(std::out_of_range&)
    {
        ok = true;
    }

    assert(ok);

    PrintResult("Get invalid index", ok);
}

void RunAllTests(){
    TestVector();
    TestVectorAlgebra();
    TestVectorFunctional();
    TestVectorEnumerator();
    TestVectorRangePrime();
    TestVectorMutableImmutable();
    TestVectorErrors();
}

