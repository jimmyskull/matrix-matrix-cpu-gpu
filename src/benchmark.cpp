/* Copyright © 2013 Paulo Roberto Urio */
#include "benchmark.hpp"

#include <sys/time.h>

#include <cstddef>

namespace core {

void Benchmark::Start()
{
    gettimeofday(&begin_, NULL);
}

void Benchmark::Stop()
{
    gettimeofday(&end_, NULL);
}

float Benchmark::duration() const
{
    float secs = static_cast<float>(end_.tv_sec - begin_.tv_sec);
    float usecs = static_cast<float>(end_.tv_usec - begin_.tv_usec);

    if (usecs < 0.0f) {
        --secs;
        usecs += 1000000.0f;
    }
    return secs * 1000.0f + usecs / 1000.0f + 0.5f;
}

}  // namespace core
