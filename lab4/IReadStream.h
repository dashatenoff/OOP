#ifndef LAB4_IREADSTREAM_H
#define LAB4_IREADSTREAM_H

template<class T>
class IReadStream{
public:
    virtual ~IReadStream() = default;

    virtual void Open() = 0;
    virtual void Close() = 0;

    virtual T Read() = 0;

    virtual bool IsEndOfStream() const = 0;
};

#endif //LAB4_IREADSTREAM_H