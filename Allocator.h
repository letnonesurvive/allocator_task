#pragma once

#include <memory>

template<class Type>
class Allocator
{

public:

    using value_type = Type;

    Allocator() = default;

    explicit Allocator (size_t theMaxSize) : myMaxSize (theMaxSize) 
    {
        myPool = ::operator new (myMaxSize * sizeof (Type));
        myCurrentSize = 0;
    }

    template <class U>
    Allocator (const Allocator<U>& theAllocator) noexcept 
    {
        //cout << "Type of U: " << typeid(U).name() << endl;
        myPool = ::operator new (theAllocator.myMaxSize * sizeof (Type));
        myMaxSize = theAllocator.myMaxSize;
        myCurrentSize = theAllocator.myCurrentSize;
    }

    Type* allocate (size_t N)
    {
        if (!isSpaceAvailable (N)) {
            throw std::runtime_error ("The memory allocation limit for the number of items has been exceeded");
        }
        Type* aRes = static_cast<Type*> (myPool) + myCurrentSize;
        myCurrentSize = myCurrentSize + N;
        return aRes;        
    }

    void deallocate (Type* thePointer, size_t theCount) noexcept
    {
        if (thePointer == myPool) {
            ::operator delete (myPool, theCount);
        }
    }

    size_t max_size() noexcept
    {
        return myMaxSize;
    }

    template<class U>
    struct rebind
    {
        using other = Allocator<U>;
    };

    using propagate_on_container_copy_assignment = std::true_type;
    using propagate_on_container_move_assignment = std::true_type;
    using propagate_on_container_swap = std::true_type;


private:
    bool isSpaceAvailable (size_t N)
    {
        return (myCurrentSize + N <= myMaxSize);
    }

public:
    size_t myMaxSize;
    size_t myCurrentSize;
    void* myPool;
};