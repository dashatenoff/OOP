#ifndef LAB4_FILEREADSTREAM_H
#define LAB4_FILEREADSTREAM_H

#include <fstream>
#include <functional>
#include <stdexcept>

#include "IReadStream.h"

template<class T>
class FileReadStream
        : public IReadStream<T>{
private:
    std::ifstream file;
    std::function<T(const std::string&)>
            deserializer;

    bool opened;

public:
    FileReadStream(
            const std::string& filename,
            std::function<T(const std::string&)>
                    deserializer
    ){
        file.open(filename);

        if(!file.is_open()){
            throw std::runtime_error(
                    "Cannot open file"
            );
        }

        this->deserializer =
                deserializer;

        opened = false;
    }

    ~FileReadStream(){
        if(file.is_open()){
            file.close();
        }
    }

    void Open() override{
        opened = true;
    }

    void Close() override{
        opened = false;
    }

    bool IsEndOfStream() const override{
        return file.eof();
    }

    T Read() override{

        if(!opened){
            throw std::logic_error(
                    "Stream is closed"
            );
        }

        std::string line;

        if(!std::getline(file,line)){
            throw std::out_of_range(
                    "EndOfStream"
            );
        }

        return deserializer(line);
    }
};

#endif