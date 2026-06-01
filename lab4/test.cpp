#include <iostream>
#include <cassert>
#include <string>
#include <functional>

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


template<typename T>
void Check(const std::string& label, T expected, T actual){
    std::string status = (expected == actual) ? "OK" : "FAIL";
    std::cout << "  " << label
              << ": expected=" << expected
              << ", got=" << actual
              << " -> " << status << std::endl;
    assert(expected == actual);
}

void CheckTrue(const std::string& label, bool actual){
    std::string status = actual ? "OK" : "FAIL";
    std::cout << "  " << label
              << ": expected=true"
              << ", got=" << (actual ? "true" : "false")
              << " -> " << status << std::endl;
    assert(actual);
}

void CheckFalse(const std::string& label, bool actual){
    std::string status = (!actual) ? "OK" : "FAIL";
    std::cout << "  " << label
              << ": expected=false"
              << ", got=" << (actual ? "true" : "false")
              << " -> " << status << std::endl;
    assert(!actual);
}

void CheckThrows(const std::string& label, std::function<void()> action){
    bool thrown = false;
    try{
        action();
    }
    catch(...){
        thrown = true;
    }
    std::string status = thrown ? "OK" : "FAIL";
    std::cout << "  " << label
              << ": expected=throw"
              << ", got=" << (thrown ? "throw" : "no throw")
              << " -> " << status << std::endl;
    assert(thrown);
}

void BeginTest(const std::string& name){
    std::cout << "[" << name << "]" << std::endl;
}

void EndTest(const std::string& name){
    std::cout << "  => PASSED" << std::endl << std::endl;
}

//generator 

int FibonacciGenerator(Sequence<int>* seq){
    if(seq->GetLength().GetValue() == 0){
        return 0;
    }
    if(seq->GetLength().GetValue() == 1){
        return 1;
    }
    return seq->Get(seq->GetLength().GetValue() - 1) +
           seq->Get(seq->GetLength().GetValue() - 2);
}

//tests

void TestLazySequenceGet(){
    BeginTest("TestLazySequenceGet");

    LazySequence<int> seq(
        FibonacciGenerator,
        new MutableArraySequence<int>(new DynamicArray<int>(0))
    );

    Check("Get(0)", 0, seq.Get(0));
    Check("Get(1)", 1, seq.Get(1));
    Check("Get(2)", 1, seq.Get(2));
    Check("Get(3)", 2, seq.Get(3));
    Check("Get(4)", 3, seq.Get(4));
    Check("Get(5)", 5, seq.Get(5));

    EndTest("TestLazySequenceGet");
}


void TestLazySequenceSubsequence(){
    BeginTest("TestLazySequenceSubsequence");

    LazySequence<int> seq(
        FibonacciGenerator,
        new MutableArraySequence<int>(new DynamicArray<int>(0))
    );

    LazySequence<int>* sub = seq.GetSubsequence(0, 4);

    Check("sub->Get(0)", 0, sub->Get(0));
    Check("sub->Get(1)", 1, sub->Get(1));
    Check("sub->Get(2)", 1, sub->Get(2));
    Check("sub->Get(3)", 2, sub->Get(3));
    Check("sub->Get(4)", 3, sub->Get(4));

    delete sub;
    EndTest("TestLazySequenceSubsequence");
}

void TestLazySequenceLength(){
    BeginTest("TestLazySequenceLength");

    LazySequence<int> seq(
        FibonacciGenerator,
        new MutableArraySequence<int>(new DynamicArray<int>(0))
    );

    CheckTrue("GetLength().IsInfinite()", seq.GetLength().IsInfinite());

    EndTest("TestLazySequenceLength");
}

void TestLazySequenceExceptions(){
    BeginTest("TestLazySequenceExceptions");

    LazySequence<int> seq(
        new MutableArraySequence<int>(new DynamicArray<int>(0))
    );

    CheckThrows("Get(0) on empty", [&](){ seq.Get(0); });

    EndTest("TestLazySequenceExceptions");
}

void TestFiniteSequenceBasic(){
    BeginTest("TestFiniteSequenceBasic");

    int items[] = {10, 20, 30, 40, 50};
    LazySequence<int> seq(items, 5);

    Check("GetLength()", (size_t)5, seq.GetLength().GetValue());
    CheckFalse("GetLength().IsInfinite()", seq.GetLength().IsInfinite());
    Check("GetFirst()", 10, seq.GetFirst());
    Check("GetLast()", 50, seq.GetLast());
    Check("Get(0)", 10, seq.Get(0));
    Check("Get(2)", 30, seq.Get(2));
    Check("Get(4)", 50, seq.Get(4));

    EndTest("TestFiniteSequenceBasic");
}


void TestAppendOnInfinite(){
    BeginTest("TestAppendOnInfinite");

    LazySequence<int> seq(
        FibonacciGenerator,
        new MutableArraySequence<int>(new DynamicArray<int>(0))
    );

    seq.Append(999);

    Check("GetLast() returns appended item", 999, seq.GetLast());

    EndTest("TestAppendOnInfinite");
}

void TestInsertAtOnInfinite(){
    BeginTest("TestInsertAtOnInfinite");

    LazySequence<int> seq(
        FibonacciGenerator,
        new MutableArraySequence<int>(new DynamicArray<int>(0))
    );

    seq.InsertAt(42, 3);

    Check("Get(0) unchanged", 0, seq.Get(0));
    Check("Get(1) unchanged", 1, seq.Get(1));
    Check("Get(2) unchanged", 1, seq.Get(2));
    Check("Get(3) inserted", 42, seq.Get(3));
    Check("Get(4) shifted", 2, seq.Get(4));

    EndTest("TestInsertAtOnInfinite");
}


void TestInsertAtOutOfRange(){
    BeginTest("TestInsertAtOutOfRange");

    int items[] = {1, 2, 3};
    LazySequence<int> seq(items, 3);

    CheckThrows("InsertAt(99, 10) out of range", [&](){ seq.InsertAt(99, 10); });

    EndTest("TestInsertAtOutOfRange");
}


void TestInsertInfiniteSequenceAtOnInfinite(){
    BeginTest("TestInsertInfiniteSequenceAtOnInfinite");

    // seq1: 0, 1, 2, 3, 
    std::function<int(Sequence<int>*)> naturals = [](Sequence<int>* s) -> int {
        return (int)s->GetLength().GetValue();
    };
    LazySequence<int> seq(naturals, new MutableArraySequence<int>(new DynamicArray<int>(0)));

    std::function<int(Sequence<int>*)> naturals100 = [](Sequence<int>* s) -> int {
        return (int)s->GetLength().GetValue() + 100;
    };
    auto* seq2 = new LazySequence<int>(naturals100, new MutableArraySequence<int>(new DynamicArray<int>(0)));

    // вставляем seq2 в позицию 3
    seq.InsertSequenceAt(seq2, 3);

    CheckTrue("GetLength() is infinite", seq.GetLength().IsInfinite());
    Check("Get(0) unchanged", 0, seq.Get(0));
    Check("Get(1) unchanged", 1, seq.Get(1));
    Check("Get(2) unchanged", 2, seq.Get(2));
    Check("Get(3) = seq2[0]", 100, seq.Get(3));
    Check("Get(4) = seq2[1]", 101, seq.Get(4));
    Check("Get(10) = seq2[7]", 107, seq.Get(10));

    EndTest("TestInsertInfiniteSequenceAtOnInfinite");
}

void TestStreams(){
    BeginTest("TestStreams");

    auto* seq =
            new MutableArraySequence<int>(
                    new DynamicArray<int>(0)
            );

    SequenceWriteStream<int> out(seq);

    out.Open();

    out.Write(10);
    out.Write(20);
    out.Write(30);

    out.Close();

    SequenceReadStream<int> in(seq);

    in.Open();

    Check("Read first", 10, in.Read());
    Check("Read second", 20, in.Read());
    Check("Read third", 30, in.Read());

    CheckTrue(
            "End of stream",
            in.IsEndOfStream()
    );

    in.Close();

    delete seq;

    EndTest("TestStreams");
}

void TestTuringMachine(){
    BeginTest("TestTuringMachine");

    auto* list =
            new LinkedList<char>();

    list->Append('1');
    list->Append('1');
    list->Append('1');

    auto* tape =
            new Tape<char>(
                    new MutableListSequence<char>(list),
                    '_'
            );

    auto* rules =
            new MutableArraySequence<Rule>(
                    new DynamicArray<Rule>(0)
            );

    rules->Append(
            Rule("q0",'1','0','R',"q0")
    );

    rules->Append(
            Rule("q0",'_','_','R',"halt")
    );

    TuringMachine tm(
            tape,
            rules
    );

    tm.Run();

    Check("Cell 0", '0', tape->Get(0));
    Check("Cell 1", '0', tape->Get(1));
    Check("Cell 2", '0', tape->Get(2));

    CheckTrue(
            "Machine halted",
            tm.IsHalt()
    );

    delete tape;
    delete rules;

    EndTest("TestTuringMachine");
}

void RunLazySequenceTests(){
    TestLazySequenceGet();
    TestLazySequenceSubsequence();
    TestLazySequenceLength();
    TestFiniteSequenceBasic();
    TestAppendOnInfinite();
    TestInsertAtOutOfRange();
    TestInsertInfiniteSequenceAtOnInfinite();
    TestStreams();
    TestTuringMachine();

    std::cout << "=== All LazySequence tests passed ===" << std::endl;
}

void RunAllTests(){
    RunLazySequenceTests();
    std::cout << "=== All tests passed ===" << std::endl;
}
