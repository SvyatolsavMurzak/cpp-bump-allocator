#include <cstddef>
#include <cstdlib>
#include <iostream>

struct BumpAllocator {
    char* buffer;
    size_t capacity;
    size_t offset;
};

void allocator_init (BumpAllocator& al, size_t size) {
    al.buffer = (char*)std::malloc(size);
    al.offset = 0;
    al.capacity = size;  
}

void* allocator_alloc (BumpAllocator& al, size_t size) {
    if (al.offset + size > al.capacity) {
        return nullptr;
    }

    void* ptr = &al.buffer[al.offset];
    al.offset += size;
    return ptr;
}

void allocator_reset (BumpAllocator& al) {
    al.offset = 0;
}

void allocator_destroy (BumpAllocator& al) {
    std::free(al.buffer);
    al.buffer = nullptr;
    al.capacity = 0;
    al.offset = 0;
}
