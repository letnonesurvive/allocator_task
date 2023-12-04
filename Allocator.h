#pragma once

#include <memory>

template<class Type>
class Allocator
{

public:

    using value_type = Type;

    Allocator() = default;

    explicit Allocator(size_t theMaxSize) : myMaxSize (theMaxSize) {}

    template <class U>
    Allocator(const Allocator<U>&) noexcept {}

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

    void deallocate (Type* thePointer, size_t) noexcept
    {
        std::free (thePointer);
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
    size_t myMaxSize = 100;
};