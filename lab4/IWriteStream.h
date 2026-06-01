#ifndef LAB4_IWRITESTREAM_H
#define LAB4_IWRITESTREAM_H

template<class T>
class IWriteStream{
public:
    virtual ~IWriteStream() = default;

    virtual void Open() = 0;
    virtual void Write(const T& item) = 0;
    virtual void Close() = 0;
    virtual size_t GetPosition() const = 0;
};

#endif //LAB4_IWRITESTREAM_H
