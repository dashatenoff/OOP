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

using namespace std;

int plus1(int x) { return x + 1; }
bool isEven(int x) { return x % 2 == 0; }
int sum(int a, int b) { return a + b; }

static void PrintResult(const char* name, bool ok)
{
    cout << name << ": " << (ok ? "OK" : "FAIL") << endl;
}

static void TestDynamicArray()
{
    cout << "\n========== TestDynamicArray ==========\n";

    int arr[] = {1,2,3};
    DynamicArray<int> da(arr,3);

    bool ok;

    ok = (da.Get(0) == 1);
    PrintResult("Get", ok);

    ok = (da.GetSize() == 3);
    PrintResult("GetSize", ok);

    da.Set(1,10);

    ok = (da.Get(1) == 10);
    PrintResult("Set", ok);
}

static void TestLinkedList()
{
    cout << "\n========== TestLinkedList ==========\n";

    int arr[] = {1,2,3};
    LinkedList<int> list(arr,3);

    list.Append(4);
    bool ok;

    ok = (list.GetLast() == 4);
    PrintResult("Append", ok);

    list.Prepend(0);

    ok = (list.GetFirst() == 0);
    PrintResult("Prepend", ok);
}

static void TestSequenceOperations()
{
    cout << "\n========== TestSequenceOperations ==========\n";

    int arr[] = {1,2,3};

    Sequence<int>* seq =
            new MutableArraySequence<int>(new DynamicArray<int>(arr,3));

    bool ok;

    seq->Append(4);
    ok = (seq->Get(3) == 4);
    PrintResult("Append", ok);

    seq->Prepend(0);
    ok = (seq->Get(0) == 0);
    PrintResult("Prepend", ok);

    seq->InsertAt(5,2);
    ok = (seq->Get(2) == 5);
    PrintResult("InsertAt", ok);

    Sequence<int>* sub = seq->GetSubsequence(1,3);

    ok = (sub->GetLength() == 3 &&
          sub->Get(0) == 2 &&
          sub->Get(1) == 5 &&
          sub->Get(2) == 3);

    PrintResult("GetSubsequence", ok);

    delete seq;
    delete sub;
}

static void TestConcat()
{
    cout << "\n========== TestConcat ==========\n";

    int a[] = {1,2};
    int b[] = {3,4};

    Sequence<int>* A =
            new MutableArraySequence<int>(new DynamicArray<int>(a,2));

    Sequence<int>* B =
            new MutableArraySequence<int>(new DynamicArray<int>(b,2));

    A->Concat(B);

    bool ok =
            (A->GetLength() == 4 &&
             A->Get(0) == 1 &&
             A->Get(1) == 2 &&
             A->Get(2) == 3 &&
             A->Get(3) == 4);

    PrintResult("Concat", ok);

    delete A;
    delete B;
}

static void TestMapWhereReduce()
{
    cout << "\n========== TestMapWhereReduce ==========\n";

    int arr[] = {1,2,3,4};

    Sequence<int>* seq =
            new MutableArraySequence<int>(new DynamicArray<int>(arr,4));

    Sequence<int>* mapped = seq->Map(plus1);
    Sequence<int>* filtered = seq->Where(isEven);
    int r = seq->Reduce(sum,0);

    bool ok;

    ok = (mapped->Get(0) == 2 &&
          mapped->Get(1) == 3 &&
          mapped->Get(2) == 4 &&
          mapped->Get(3) == 5);

    PrintResult("Map", ok);

    ok = (filtered->GetLength() == 2 &&
          filtered->Get(0) == 2 &&
          filtered->Get(1) == 4);

    PrintResult("Where", ok);

    ok = (r == 10);
    PrintResult("Reduce", ok);

    delete seq;
    delete mapped;
    delete filtered;
}

static void TestImmutable()
{
    cout << "\n========== TestImmutable ==========\n";

    int arr[] = {1,2,3};

    Sequence<int>* seq =
            new ImmutableArraySequence<int>(new DynamicArray<int>(arr,3));

    Sequence<int>* newSeq = seq->Append(4);

    bool ok1 = (seq->GetLength() == 3);
    bool ok2 = (newSeq->GetLength() == 4 && newSeq->Get(3) == 4);

    PrintResult("Immutable original unchanged", ok1);
    PrintResult("Immutable returns new object", ok2);

    delete seq;
    delete newSeq;
}

static void TestErrors()
{
    cout << "\n========== TestErrors ==========\n";

    int arr[] = {1,2,3};

    Sequence<int>* seq =
            new MutableArraySequence<int>(new DynamicArray<int>(arr,3));

    bool ok1 = false;

    try
    {
        seq->Get(10);
    }
    catch(const out_of_range&)
    {
        ok1 = true;
    }

    PrintResult("Get index error", ok1);

    bool ok2 = false;

    try
    {
        seq->InsertAt(5,-1);
    }
    catch(const out_of_range&)
    {
        ok2 = true;
    }

    PrintResult("InsertAt index error", ok2);

    delete seq;
}

static void TestEnumerator()
{
    cout << "\n========== TestEnumerator ==========\n";

    int arr[] = {1,2,3};

    Sequence<int>* seq =
            new MutableArraySequence<int>(new DynamicArray<int>(arr,3));

    IEnumerator<int>* it = seq->GetEnumerator();

    int s = 0;

    while(it->MoveNext())
    {
        s += it->Current();
    }

    bool ok = (s == 6);

    PrintResult("Enumerator iteration", ok);

    delete it;
    delete seq;
}

void RunAllTests()
{
    cout << "\n========================\n";
    cout << "RUNNING TESTS\n";
    cout << "========================\n";

    TestDynamicArray();
    TestLinkedList();
    TestSequenceOperations();
    TestConcat();
    TestMapWhereReduce();
    TestErrors();
    TestImmutable();
    TestEnumerator();

    cout << "\n========================\n";
    cout << "ALL TESTS FINISHED\n";
    cout << "========================\n";
}