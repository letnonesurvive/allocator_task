#pragma once

#include <memory>

template<class Type, class Allocator = std::allocator<Type>>
class container
{
public:

    container()
    {
        myBuf = std::allocator_traits<Allocator>::allocate (myAllocator, 1);
    }

    explicit container (size_t theLength)
    {
        myCapacity = theLength;
        myBuf = std::allocator_traits<Allocator>::allocate (myAllocator, myCapacity);
    }

    explicit container (const Allocator& theAllocator) : myAllocator (theAllocator)
    {
        myBuf = std::allocator_traits<Allocator>::allocate (myAllocator, myAllocator.max_size());
    }

    void push_back (const Type& theValue)
    {
        /*if (mySize == myCapacity) {
            myCapacity = myCapacity * 2 + 1;
            Type* aNewData = std::allocator_traits<Allocator>::allocate (myAllocator, myCapacity);
            std::copy (myBuf, myBuf + mySize * sizeof (Type), aNewData);
            std::swap (aNewData, myBuf);
            std::allocator_traits<Allocator>::deallocate (myAllocator, aNewData, myCapacity);
        }*/

        std::allocator_traits<Allocator>::construct (myAllocator, myBuf + mySize, theValue);
        ++mySize;
    }

    bool has_next()
    {
        if (myIteratorIndex != mySize) {
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

    size_t size()
    {
        return mySize;
    }

    bool empty()
    {
        return (mySize == 0);
    }

    ~container()
    {
        std::allocator_traits<Allocator>::deallocate (myAllocator, myBuf, mySize);
    }

private:

    Type* myBuf = nullptr;
    size_t mySize = 0;
    size_t myIteratorIndex = 0;
    size_t myCapacity = 0;

    Allocator myAllocator;
};
