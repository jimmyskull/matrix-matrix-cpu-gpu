/* Copyright © 2013 Paulo Roberto Urio */

#ifndef RANDOM_H_
#define RANDOM_H_

#include <cstdint>

#include <random>

namespace core {

/*
 * Uniform real distribution random number generator, using Mersenne
 * twister MT19937.  The engine is seeded with priority on a given
 * seed by the command line.  Otherwise, the seed is generated on
 * the construction, using random_device, which is a non-deterministic
 * uniform random number.
 */
class Random {
public:
    Random();

    ~Random();

    /*
     * Write into |output| |choices| random values based on |seed|.
     * Produces random floating-point values in the interval [0, 1)
     */
    void generate(int choices, double* output);

    /*
     * Generate a floating-point value in the interval [0, 1).
     */
    double next()
    {
        return distribution_(mersenne_engine_);
    }

    /*
     * Generate a floating-point using |distribution|.
     */
    template<typename T>
    T next(std::uniform_real_distribution<T>* distribution)
    {
        return (*distribution)(mersenne_engine_);
    }

    /*
     * Generate an integer using |distribution|.
     */
    template<typename T>
    int next(std::uniform_int_distribution<T>* distribution)
    {
        return (*distribution)(mersenne_engine_);
    }

    uint64_t seed() const;

    std::mt19937& engine()
    {
        return mersenne_engine_;
    }

private:
    void set_seed(uint64_t seed);

    uint64_t seed_;
    std::uniform_real_distribution<double> distribution_;
    std::mt19937 mersenne_engine_;  // Mersenne twister MT19937
};

}  // namespace moead

#endif  // RANDOM_H_
