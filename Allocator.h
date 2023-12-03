#pragma once

#include <memory>

template<class Type>
class Allocator
{

public:

    using value_type = Type;

    Allocator() = default;


    Type* allocate (size_t N)
    {
        if (N > myMaxSize) {
            throw std::exception ("The memory allocation limit for the number of items has been exceeded");
        }

        if (void* aPointer = std::malloc (N * sizeof (Type))) {
            return static_cast<Type*> (aPointer);
        }
        throw std::bad_alloc();
    }

    void deallocate (Type* thePointer, size_t N) noexcept
    {
        (void)N;
        std::free (thePointer);
    }

private:
    size_t myMaxSize = 100;
};