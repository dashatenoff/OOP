#ifndef LAB4_FILEWRITESTREAM_H
#define LAB4_FILEWRITESTREAM_H

#include <fstream>
#include <functional>
#include <stdexcept>
#include <string>

#include "IWriteStream.h"

template<class T>
class FileWriteStream : public IWriteStream<T>{
protected:
    std::string filepath;
    std::ofstream fileOut;
    std::function<std::string(const T&)> serializer;
    size_t position;
    bool opened;
public:
    FileWriteStream(const std::string& filename, std::function<std::string(const T&)> serializer){
        this->filepath = filename;
        this->serializer = serializer;
        position = 0;
        opened = false;
    }

    ~FileWriteStream(){
        if(fileOut.is_open()){
            fileOut.close();
        }
    }

    void Open() override{
        fileOut.open(filepath);
        if(!fileOut.is_open()){
            throw std::runtime_error("Cannot open file: " + filepath);
        }
        opened = true;
    }

    void Close() override{
        if(fileOut.is_open()){
            fileOut.close();
        }
        opened = false;
    }

    size_t GetPosition() const override{
        return position;
    }

    void Write(const T& item) override{
        if(!opened){
            throw std::logic_error("Stream is closed");
        }
        fileOut << serializer(item) << "\n";
        position++;
    }
};

#endif //LAB4_FILEWRITESTREAM_H
