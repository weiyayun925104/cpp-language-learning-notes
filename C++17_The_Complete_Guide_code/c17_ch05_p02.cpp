#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <memory_resource>
#include <memory>
#include <new>       // for std::align_val_t
#include <cstdio>    // for printf()
#include <cstdlib>   // for malloc() and aligned_alloc()

class TrackNew
{
private:
    static inline int numMalloc = 0;    // num malloc calls
    static inline size_t sumSize = 0;   // bytes allocated so far
    static inline bool doTrace = false; // tracing enabled
    static inline bool inNew = false;   // don't track output inside new overloads
public:
    static void reset()                 // reset new/memory counters
    {
        numMalloc = 0;
        sumSize = 0;
    }

    static void trace(bool b)           // enable/disable tracing
    {
        doTrace = b;
    }

    // implementation of tracked allocation:
    static void *allocate(std::size_t size, std::size_t align, const char *call)
    {
        // trace output might again allocate memory, so handle this the usual way:
        if (inNew)
        {
            void *p;
            if (align == 0)
            {
                p = std::malloc(size);
            }
            else
            {
                p = std::aligned_alloc(align, size);  // C++17 API
            }
            return p;
        }

        inNew = true;
        // track and trace the allocation:
        ++numMalloc;
        sumSize += size;
        void *p;
        if (align == 0)
        {
            p = std::malloc(size);
        }
        else
        {
            p = std::aligned_alloc(align, size);  // C++17 API
        }
        if (doTrace)
        {
            std::cerr << "#" << numMalloc << " "
                      << call << " (" << size << " Bytes " << align << "aligned) => "
                      << p << " (total: " << sumSize << " Bytes)" << '\n';
        }
        inNew = false;
        return p;
    }

    static void status()                // print current state
    {
        std::cerr << numMalloc << " mallocs for " << sumSize << " Bytes" << '\n';
    }
};

[[nodiscard]]
void *operator new (std::size_t size)
{
    return TrackNew::allocate(size, 0, "::new");
}

[[nodiscard]]
void *operator new (std::size_t size, std::align_val_t align)
{
    return TrackNew::allocate(size, static_cast<size_t>(align),
                              "::new aligned");
}

[[nodiscard]]
void *operator new[] (std::size_t size)
{
    return TrackNew::allocate(size, 0, "::new[]");
}

[[nodiscard]]
void *operator new[] (std::size_t size, std::align_val_t align)
{
    return TrackNew::allocate(size, static_cast<size_t>(align),
                              "::new[] aligned");
}

// ensure deallocations match:
void operator delete (void *p) noexcept
{
    std::free(p);
}
void operator delete (void *p, std::size_t) noexcept
{
    ::operator delete(p);
}
void operator delete (void *p, std::align_val_t) noexcept
{
    std::free(p);      // C++17 API
}

void operator delete (void *p, std::size_t,
                      std::align_val_t align) noexcept
{
    ::operator delete(p, align);
}

int main()
{
    TrackNew::reset();

    // allocate some memory on the stack:
    std::array<std::byte, 200000> buf;

    // and use it as initial memory pool for a vector:
    std::pmr::monotonic_buffer_resource pool{buf.data(), buf.size()};
    std::pmr::vector<std::string> coll{&pool};

    for (int i = 0; i < 1000; ++i)
    {
        coll.emplace_back("just a non-SSO string");
    }

    TrackNew::status();
}
