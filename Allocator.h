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
        myCurrentPos = myPool;
    }

    template <class U>
    Allocator (const Allocator<U>& theAllocator) noexcept 
    {
        myPool = ::operator new (theAllocator.myMaxSize * sizeof (Type));
        myMaxSize = theAllocator.myMaxSize;
        myCurrentPos = myPool;
    }

    Type* allocate (size_t N)
    {
        Type* aRes = static_cast<Type*> (myCurrentPos);
        if (!isSpaceAvailable (N)) {
            throw std::runtime_error ("The memory allocation limit for the number of items has been exceeded");
        }
        myCurrentPos = static_cast<Type*>(myCurrentPos) + N;
        return aRes;        
    }

    void deallocate (Type* thePointer, size_t) noexcept
    {
        //std::free (myPool);
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

    //~Allocator()
    //{
    //    //delete myPool;
    //    //delete myCurrentPos
    //}

private:
    bool isSpaceAvailable (size_t N)
    {
        Type* aWillBeAllocated = static_cast <Type*>(myCurrentPos) + N;
        bool aRes = aWillBeAllocated <= static_cast <Type*>(myPool) + sizeof(Type) * max_size();
        return aRes;
    }

public:
    size_t myMaxSize;
    void* myPool;
    void* myCurrentPos;
};