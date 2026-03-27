#include <iostream>

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
    cout << name << ": " << (ok ? "OK" : "FAIL") << "\n";
}

static void TestDynamicArray()
{
    cout << "\n=== TestDynamicArray ===\n";

    int arr[] = {1,2,3};

    DynamicArray<int> da(arr,3);

    bool ok1 = (da.Get(0) == 1);
    bool ok2 = (da.GetSize() == 3);

    da.Set(1,10);
    bool ok3 = (da.Get(1) == 10);

    PrintResult("Get", ok1);
    PrintResult("GetSize", ok2);
    PrintResult("Set", ok3);
}

static void TestLinkedList()
{
    cout << "\n=== TestLinkedList ===\n";

    int arr[] = {1,2,3};

    LinkedList<int> list(arr,3);

    list.Append(4);

    bool ok1 = (list.GetLast() == 4);

    list.Prepend(0);

    bool ok2 = (list.GetFirst() == 0);

    PrintResult("Append", ok1);
    PrintResult("Prepend", ok2);
}



static void TestSequenceOperations()
{
    cout << "\n========== TestSequenceOperations ==========\n";

    int arr[] = {1,2,3};

    Sequence<int>* seq =
            new MutableArraySequence<int>(new DynamicArray<int>(arr,3));

    seq->Append(4);
    bool ok1 = (seq->Get(3) == 4);

    seq->Prepend(0);
    bool ok2 = (seq->Get(0) == 0);

    seq->InsertAt(5,2);
    bool ok3 = (seq->Get(2) == 5);

    Sequence<int>* sub = seq->GetSubsequence(1,3);
    bool ok4 = (sub->GetLength() == 3);

    PrintResult("Append", ok1);
    PrintResult("Prepend", ok2);
    PrintResult("InsertAt", ok3);
    PrintResult("GetSubsequence", ok4);

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

    bool ok = (A->GetLength() == 4 && A->Get(3) == 4);

    PrintResult("Concat", ok);

    delete A;
    delete B;
}

static void TestMapWhereReduce()
{
    cout << "\n=== TestMapWhereReduce ===\n";

    int arr[] = {1,2,3,4};

    Sequence<int>* seq =
            new MutableArraySequence<int>(new DynamicArray<int>(arr,4));

    Sequence<int>* mapped = seq->Map(plus1);
    Sequence<int>* filtered = seq->Where(isEven);
    int r = seq->Reduce(sum,0);

    bool ok1 = (mapped->Get(0) == 2);
    bool ok2 = (filtered->GetLength() == 2);
    bool ok3 = (r == 10);

    PrintResult("Map", ok1);
    PrintResult("Where", ok2);
    PrintResult("Reduce", ok3);

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
    bool ok2 = (newSeq->GetLength() == 4);

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

    bool ok2 = false;

    try
    {
        seq->InsertAt(5,-1);
    }
    catch(const out_of_range&)
    {
        ok2 = true;
    }

    PrintResult("Get index error", ok1);
    PrintResult("InsertAt index error", ok2);

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

    cout << "\n========================\n";
    cout << "ALL TESTS FINISHED\n";
    cout << "========================\n";
}

