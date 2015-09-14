/* Copyright © 2013 Paulo Roberto Urio */
#ifndef BENCHMARK_H_
#define BENCHMARK_H_

#include <ctime>

namespace core {

/*
 * Benchmark is a single-threaded instance to measure time
 * difference between two points.  You may use its C++11
 * version, function |measure()| should receive a lambda
 * function:
 *
 * Benchmark bm;
 * float duration = bm.measure([=]() {
 *      ...
 *      block of code to be measured;
 *      ...
 *  });
 */
class Benchmark {
public:
    Benchmark() = default;

    ~Benchmark() = default;

    Benchmark(const Benchmark&) = delete;

    void operator =(const Benchmark&) = delete;

    /*
     * Call |f| measuring its time and returns the function duration
     * in milliseconds.
     */
    template<typename F>
    float measure(F f)
    {
        Start();
        f();
        Stop();
        return duration();
    }

    /* Save start time */
    void Start();

    /* Save stop time */
    void Stop();

    /*
     * Returns the time spent in milliseconds between last
     * calls of Start() and Stop().
     */
    float duration() const;

private:
    timeval begin_;
    timeval end_;
};

}  // namespace core

#endif  // BENCHMARK_H_
