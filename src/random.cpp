/* Copyright © 2013 Paulo Roberto Urio */
#include "random.hpp"

#include <cstdint>

#include <algorithm>
#include <functional>
#include <random>

#include "debug.hpp"

namespace core {

Random::Random()
{
    uint64_t seed;

    std::random_device rnd_device;
    seed = static_cast<uint64_t>(rnd_device());
    set_seed(seed);
}

Random::~Random()
{
}

void Random::set_seed(uint64_t seed)
{
    printd(TESTING, "seed = %lu\n", seed);
    mersenne_engine_.seed(seed);
    seed_ = seed;
}

void Random::generate(int choices, float* output)
{
    auto generator = std::bind(distribution_, mersenne_engine_);

    std::generate(output, output + choices, generator);
}

uint64_t Random::seed() const
{
    return seed_;
}

}  // namespace moead
