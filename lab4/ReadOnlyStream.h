#ifndef LAB4_READONLYSTREAM_H
#define LAB4_READONLYSTREAM_H

#include <stdexcept>
#include <fstream>
#include <sstream>
#include <functional>

#include "Sequence.h"
#include "MutableArraySequence.h"
#include "DynamicArray.h"

template<class T>
class ReadOnlyStream{
protected:
    Sequence<T>* sequence;
    size_t position;
    bool opened;
    bool canSeek;
    bool canGoBack;

public:
    ReadOnlyStream(Sequence<T>* seq){
        this->sequence = seq;
        position = 0;
        opened = false;
        canSeek = true;
        canGoBack = true;
    }

    ReadOnlyStream(const std::string& filename, std::function<T(const std::string&)> deserializer){
        auto* seq = new MutableArraySequence<T>(new DynamicArray<T>(0));
        std::ifstream file(filename);

        if(!file.is_open()){
            throw std::runtime_error("Cannot open file: " + filename);
        }

        std::string line;
        while(std::getline(file, line)){
            if(!line.empty()){
                seq->Append(deserializer(line));
            }
        }

        file.close();
        this->sequence = seq;
        position = 0;
        opened = false;
        canSeek = true;
        canGoBack = true;
    }

    ReadOnlyStream(const std::string& data, std::function<T(const std::string&)> deserializer, char delimiter){
        auto* seq = new MutableArraySequence<T>(new DynamicArray<T>(0));
        std::istringstream iss(data);
        std::string token;

        while(std::getline(iss, token, delimiter)){
            if(!token.empty()){
                seq->Append(deserializer(token));
            }
        }

        this->sequence = seq;
        position = 0;
        opened = false;
        canSeek = true;
        canGoBack = true;
    }

    void Open(){
        opened = true;
    }

    void Close(){
        opened = false;
    }

    bool IsEndOfStream() const{
        try{
            sequence->Get(position);
            return false;
        }
        catch(...){
            return true;
        }
    }

    T Read(){
        if(!opened){
            throw std::logic_error("Stream is closed");
        }

        if(IsEndOfStream()){
            throw std::out_of_range("EndOfStream");
        }

        return sequence->Get(position++);
    }

    size_t GetPosition() const{
        return position;
    }

    bool IsCanSeek() const{
        return canSeek;
    }

    size_t Seek(size_t index){
        if(!canSeek){
            throw std::logic_error("Seek unavailable");
        }

        try{
            sequence->Get(index);
        }
        catch(...){
            throw std::out_of_range("Seek position unavailable");
        }

        position = index;
        return position;
    }

    bool IsCanGoBack() const{
        return canGoBack;
    }

    size_t GoBack(){
        if(!canGoBack){
            throw std::logic_error("GoBack unavailable");
        }

        if(position == 0){
            throw std::out_of_range("Already at beginning of stream");
        }

        position--;
        return position;
    }
};

#endif //LAB4_READONLYSTREAM_H
