#pragma once
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunknown-pragmas"
#pragma ide diagnostic ignored "cppcoreguidelines-narrowing-conversions"

#if __cplusplus >= 201103L
#include <chrono>
#else
#include <time.h>
#endif

namespace {
#if __cplusplus >= 201103L

    inline static int64_t getCurrentTimepoint()
    {
        return std::chrono::duration_cast<std::chrono::nanoseconds>(
                   std::chrono::high_resolution_clock::now().time_since_epoch())
            .count();
    }

    // template <typename... Args>
    // inline static int64_t getCurrentTimepoint(Args&&... args)
    // {
    //     return getCurrentTimepoint();
    // }

#else

    inline long getCurrentTimepoint() {
        timespec tp{};
        clock_gettime(/*CLOCK_MONOTONIC_RAW*/ CLOCK_MONOTONIC, &tp);
        // return tp.tv_nsec;
        return tp.tv_sec * 1000000000 + tp.tv_nsec;
    }

#endif
} // namespace

#pragma clang diagnostic pop
