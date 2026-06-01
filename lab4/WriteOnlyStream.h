#ifndef LAB4_WRITEONLYSTREAM_H
#define LAB4_WRITEONLYSTREAM_H

#include <stdexcept>
#include <fstream>
#include <functional>
#include <string>

#include "Sequence.h"

template<class T>
class WriteOnlyStream{
protected:
    Sequence<T>* sequence;
    std::string filepath;
    std::ofstream fileOut;
    std::function<std::string(const T&)> serializer;
    size_t position;
    bool opened;
    bool fileMode;

public:
    WriteOnlyStream(Sequence<T>* seq){
        this->sequence = seq;
        this->fileMode = false;
        position = 0;
        opened = false;
    }

    WriteOnlyStream(const std::string& filename, std::function<std::string(const T&)> serializer){
        this->sequence = nullptr;
        this->filepath = filename;
        this->serializer = serializer;
        this->fileMode = true;
        position = 0;
        opened = false;
    }

    ~WriteOnlyStream(){
        if(fileMode && fileOut.is_open()){
            fileOut.close();
        }
    }

    void Open(){
        if(fileMode){
            fileOut.open(filepath);
            if(!fileOut.is_open()){
                throw std::runtime_error("Cannot open file: " + filepath);
            }
        }
        opened = true;
    }

    void Close(){
        if(fileMode && fileOut.is_open()){
            fileOut.close();
        }
        opened = false;
    }

    size_t GetPosition() const{
        return position;
    }

    size_t Write(const T& item){
        if(!opened){
            throw std::logic_error("Stream is closed");
        }

        if(fileMode){
            fileOut << serializer(item) << "\n";
        }
        else{
            sequence->Append(item);
        }

        position++;
        return position;
    }
};

#endif //LAB4_WRITEONLYSTREAM_H
