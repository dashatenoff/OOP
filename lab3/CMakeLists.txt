cmake_minimum_required(VERSION 3.26)
project(lab3)

set(CMAKE_CXX_STANDARD 17)

add_executable(lab2
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

        Enumerator.h
        IEnumerator.h

        Vector.h
)