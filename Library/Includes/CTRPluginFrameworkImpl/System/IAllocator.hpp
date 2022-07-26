#pragma once

#include <Headers.h>

template <class T>
class IAllocator {
    public:
        typedef T value_type;
        typedef T *pointer;
        typedef const T *const_pointer;
        typedef T &reference;
        typedef const T &const_reference;
        typedef size_t size_type;
        typedef ptrdiff_t difference_type;

        // Rebind allocator to type U
        template <class U>
        struct rebind {
            typedef IAllocator<U> other;
        };

        pointer address(reference value) const {
            return &value;
        }

        const_pointer address(const_reference value) const {
            return &value;
        }

        IAllocator() {}
        IAllocator(const IAllocator&) {}

        template <class U>
        IAllocator(const IAllocator<U>&) {}

        ~IAllocator() {}

        // Return maximum number of elements that can be allocated
        size_type max_size() const {
            return numeric_limits<size_t>::max() / sizeof(T);
        }

        // Allocate but don't initialize num elements of type T
        pointer allocate(size_type num, const void* = 0) {
            pointer ret = static_cast<pointer>(CTRPluginFramework::Heap::Alloc(num * sizeof(T)));
            // Print message and allocate memory with global new
            return ret;
        }

        // Initialize elements of allocated storage p with value value
        void construct(pointer p, const T& value) {
            // Initialize memory with placement new
            if (p)
                new(static_cast<void*>(p))T(value);
        }

        // Destroy elements of initialized storage p
        void destroy(pointer p) {
            // Destroy objects by calling their destructor
            p->~T();
        }

        // Deallocate storage p of deleted elements
        void deallocate(pointer p, size_type num) {
            CTRPluginFramework::Heap::Free(p);
        }
};

template <class T1, class T2>
bool operator == (const IAllocator<T1>&, const IAllocator<T2>&) {
    return true;
}

template <class T1, class T2>
bool operator != (const IAllocator<T1>&, const IAllocator<T2>&) {
    return false;
}