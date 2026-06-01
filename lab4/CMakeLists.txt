cmake_minimum_required(VERSION 3.26)
project(lab4)

set(CMAKE_CXX_STANDARD 17)

add_executable(lab4
        main.cpp
        test.cpp

        DynamicArray.h
        LinkedList.h
        Sequence.h
        ArraySequence.h
        ListSequence.h

        MutableArraySequence.h
        ImmutableArraySequence.h

        MutableListSequence.h
        ImmutableListSequence.h

        ArrayEnumerator.h
        ListEnumerator.h
        IEnumerator.h

        Cardinal.h
        Generator.h
        Operation.h
        LazySequence.h

        ReadOnlyStream.h
        WriteOnlyStream.h
        Rule.h
        Tape.h
        TuringMachine.h
)