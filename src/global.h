#ifndef GLOBAL_H
#define GLOBAL_H

#include <random>

namespace global {
extern std::random_device rd;
extern std::mt19937 random_engine;

constexpr int number_of_sus = 10;
}  // namespace global

#endif  // GLOBAL_H
