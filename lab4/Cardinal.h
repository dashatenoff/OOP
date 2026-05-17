#ifndef LAB4_CARDINAL_H
#define LAB4_CARDINAL_H

#include <cstddef>

class Cardinal{
private:
    size_t value;
    bool infinite;

public:
    Cardinal(size_t value = 0, bool infinite = false){
        this->value = value;
        this->infinite = infinite;
    };

    bool IsInfinite() const{
        return infinite;
    };

    size_t GetValue() const{
        return value;
    };
};


#endif //LAB4_CARDINAL_H
