#ifndef TRACKNEW_HPP
#define TRACKNEW_HPP

#include <new>
#include <cstdlib>
#include <iostream>

class TrackNew
{
private:
    static inline int numMalloc = 0; // num malloc calls
    static inline long sumSize = 0; // bytes allocated so far
    static inline bool doTrace = false; // tracing enabled
    static inline bool inNew = false; // don¡¯t track output inside new overloads
public:

    // reset new/memory counters
    static void reset()
    {
        numMalloc = 0;
        sumSize = 0;
    }

    // enable print output for each new:
    static void trace(bool b)
    {
        doTrace = b;
    }

    // print current state:
    static void status()
    {
        std::cerr << numMalloc << " mallocs for " << sumSize << " Bytes" << '\n';
    }

    // implementation of tracked allocation:
    static void *allocate(std::size_t size, const char *call)
    {
        // trace output might again allocate memory, so handle this the usual way:
        if (inNew)
        {
            return std::malloc(size);
        }

        inNew = true;
        // track and trace the allocation:
        ++numMalloc;
        sumSize += size;
        void *p = std::malloc(size);
        if (doTrace)
        {
            std::cerr << "#" << numMalloc << " "
                      << call << " (" << size << " Bytes) => "
                      << p << " (total: " << sumSize << " Bytes)" << '\n';
        }
        inNew = false;
        return p;
    }
};

inline void *operator new (std::size_t size)
{
    return TrackNew::allocate(size, "::new");
}

inline void *operator new[] (std::size_t size)
{
    return TrackNew::allocate(size, "::new[]");
}

#endif
