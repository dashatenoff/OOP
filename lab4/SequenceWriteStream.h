#ifndef LAB4_SEQUENCEWRITESTREAM_H
#define LAB4_SEQUENCEWRITESTREAM_H

#include <stdexcept>

#include "IWriteStream.h"
#include "Sequence.h"

template<class T>
class SequenceWriteStream : public IWriteStream<T>{
protected:
    Sequence<T>* sequence;
    size_t position;
    bool opened;
public:
    SequenceWriteStream(Sequence<T>* seq){
        this->sequence = seq;
        position = 0;
        opened = false;
    }

    void Open() override{
        opened = true;
    }

    void Write(const T& item) override{
        if(!opened){
            throw std::runtime_error("Stream is not open");
        }
        sequence->Append(item);
        position++;
    }

    void Close() override{
        opened = false;
    }

    size_t GetPosition() const override{
        return position;
    }
};

#endif //LAB4_SEQUENCEWRITESTREAM_H
