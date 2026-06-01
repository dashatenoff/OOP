#ifndef LAB4_SEQUENCEREADSTREAM_H
#define LAB4_SEQUENCEREADSTREAM_H

#include <stdexcept>

#include "IReadStream.h"
#include "Sequence.h"

template<class T>
class SequenceReadStream: public IReadStream<T>{
private:
    Sequence<T>* sequence;
    size_t position;
    bool opened;

public:
    SequenceReadStream(Sequence<T>* sequence){
        this->sequence = sequence;
        position = 0;
        opened = false;
    }

    void Open() override{
        opened = true;
    }

    void Close() override{
        opened = false;
    }

    bool IsEndOfStream() const override{
        return position >=
               sequence->GetLength().GetValue();
    }

    T Read() override{

        if(!opened){
            throw std::logic_error(
                    "Stream is closed"
            );
        }

        if(IsEndOfStream()){
            throw std::out_of_range(
                    "EndOfStream"
            );
        }

        return sequence->Get(position++);
    }

    void Seek(size_t index){
        position = index;
    }
};

#endif