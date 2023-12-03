#pragma once

#include <memory>

template<class Type, class Allocator = std::allocator<Type>>
class container
{
public:

    container() : mySize (0), myIteratorIndex (0), myCapacity (0)
    {
        myBuf = std::allocator_traits<Allocator>::allocate (myAllocator, 1);
    }

    container (size_t theLength) : mySize (0), myIteratorIndex (0)
    {
        //myBuf = std::shared_ptr<Type[]>(new Type[theLength]);

        myCapacity = theLength * 2 + 1;
        myBuf = std::allocator_traits<Allocator>::allocate (myAllocator, myCapacity);
    }

    void push_back (const Type& theValue)
    {
        if (mySize == myCapacity) {
            myCapacity = myCapacity * 2 + 1;
            Type* aNewData = std::allocator_traits<Allocator>::allocate (myAllocator, myCapacity);
            std::copy (myBuf, myBuf + mySize * sizeof (Type), aNewData);
            std::swap (aNewData, myBuf);
            std::allocator_traits<Allocator>::deallocate (myAllocator, aNewData, myCapacity);
        }

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

private:

    Type* myBuf;
    size_t mySize;
    size_t myIteratorIndex;
    size_t myCapacity;

    Allocator myAllocator;
};
