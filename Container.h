#pragma once

#include <memory>

template<class Type, class Allocator = std::allocator<Type>>
class container
{
public:

    container() = default;

    container (size_t theLength)
    {
        //myBuf = new Type [theLength]; // should be delegated to allocator
        myBuf = std::shared_ptr<Type[]>(new Type[theLength]);
        mySize = theLength;
        myCurrentIndex = 0;
        myIteratorIndex = 0;
    }

    void push_back (const Type& theValue)
    {
        // if capacity == size
        myBuf[myCurrentIndex] = theValue;
        myCurrentIndex++;
    }

    bool has_next()
    {
        if (myIteratorIndex != myCurrentIndex) {
            return true;
        }
        else {
            myIteratorIndex = 0;
        }
        return false;
    }

    Type next()
    {
        return myBuf[myIteratorIndex++];
    }

    ~container() 
    {

    }

private:

    std::shared_ptr<Type[]> myBuf;
    size_t mySize;
    size_t myCurrentIndex;
    size_t myIteratorIndex;
};
