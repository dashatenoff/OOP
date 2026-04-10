#include <cassert>
#include <iostream>

#include "DynamicArray.h"
#include "LinkedList.h"
#include "MutableArraySequence.h"
#include "MutableListSequence.h"

using namespace std;

static int plus1(const int& x) { return x + 1; }
static bool isEven(const int& x) { return x % 2 == 0; }
static int sum(const int& a, const int& b) { return a + b; }

void TestDynamicArray(){

    cout << "\nDynamicArray test\n";

    int arr[3] = {1,2,3};

    DynamicArray<int> a(arr,3);

    cout << "Size expected: 3, got: " << a.GetSize() << endl;
    assert(a.GetSize() == 3);

    cout << "Element[0] expected: 1, got: " << a.Get(0) << endl;
    assert(a.Get(0) == 1);

    cout << "Element[2] expected: 3, got: " << a.Get(2) << endl;
    assert(a.Get(2) == 3);

    a.Set(1,5);

    cout << "After Set index 1 expected: 5, got: " << a.Get(1) << endl;
    assert(a.Get(1) == 5);

    a.Resize(5);

    cout << "Size after Resize expected: 5, got: " << a.GetSize() << endl;
    assert(a.GetSize() == 5);
}

void TestLinkedList(){

    cout << "\nLinkedList test\n";

    int arr[3] = {1,2,3};

    LinkedList<int> list(arr,3);

    cout << "Size expected: 3, got: " << list.GetLength() << endl;
    assert(list.GetLength() == 3);

    cout << "First expected: 1, got: " << list.GetFirst() << endl;
    assert(list.GetFirst() == 1);

    cout << "Last expected: 3, got: " << list.GetLast() << endl;
    assert(list.GetLast() == 3);

    list.Append(4);

    cout << "After Append size expected: 4, got: " << list.GetLength() << endl;
    assert(list.GetLength() == 4);

    cout << "Last element expected: 4, got: " << list.Get(3) << endl;
    assert(list.Get(3) == 4);

    list.Prepend(0);

    cout << "After Prepend first expected: 0, got: " << list.GetFirst() << endl;
    assert(list.GetFirst() == 0);
}

void TestSequence(){

    cout << "\nSequence test\n";

    int arr[3] = {1,2,3};

    Sequence<int>* seq =
            new MutableArraySequence<int>(new DynamicArray<int>(arr,3));

    seq->Append(4);

    cout << "Append size expected: 4, got: " << seq->GetLength() << endl;
    assert(seq->GetLength() == 4);

    cout << "Last element expected: 4, got: " << seq->Get(3) << endl;
    assert(seq->Get(3) == 4);

    seq->Prepend(0);

    cout << "Prepend first expected: 0, got: " << seq->Get(0) << endl;
    assert(seq->Get(0) == 0);

    seq->InsertAt(100,2);

    cout << "InsertAt index 2 expected: 100, got: " << seq->Get(2) << endl;
    assert(seq->Get(2) == 100);

    delete seq;
}

void TestMapWhereReduce(){

    cout << "\nMap / Where / Reduce test\n";

    int arr[4] = {1,2,3,4};

    Sequence<int>* seq =
            new MutableArraySequence<int>(new DynamicArray<int>(arr,4));

    Sequence<int>* mapped = seq->Map(plus1);

    cout << "Map first expected: 2, got: " << mapped->Get(0) << endl;
    assert(mapped->Get(0) == 2);

    cout << "Map last expected: 5, got: " << mapped->Get(3) << endl;
    assert(mapped->Get(3) == 5);

    Sequence<int>* filtered = seq->Where(isEven);

    cout << "Where size expected: 2, got: " << filtered->GetLength() << endl;
    assert(filtered->GetLength() == 2);

    cout << "Where first expected: 2, got: " << filtered->Get(0) << endl;
    assert(filtered->Get(0) == 2);

    int r = seq->Reduce(sum,0);

    cout << "Reduce expected: 10, got: " << r << endl;
    assert(r == 10);

    delete seq;
    delete mapped;
    delete filtered;
}

void TestEnumerator(){

    cout << "\nEnumerator test\n";

    int arr[4] = {1,2,3,4};

    Sequence<int>* seq =
            new MutableArraySequence<int>(new DynamicArray<int>(arr,4));

    IEnumerator<int>* it = seq->GetEnumerator();

    int total = 0;
    int count = 0;

    while(it->MoveNext()){
        total += it->Current();
        count++;
    }

    cout << "Enumerator count expected: 4, got: " << count << endl;
    assert(count == seq->GetLength());

    cout << "Enumerator sum expected: 10, got: " << total << endl;
    assert(total == 10);

    delete it;
    delete seq;
}

void RunAllTests(){

    cout << "\n===== RUNNING TESTS =====\n";

    TestDynamicArray();
    TestLinkedList();
    TestSequence();
    TestMapWhereReduce();
    TestEnumerator();

    cout << "\n===== ALL TESTS PASSED =====\n";
}