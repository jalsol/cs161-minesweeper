#ifndef GLOBAL_H
#define GLOBAL_H

#include <random>

#include "raylib.h"

namespace global {
extern std::random_device rd;
extern std::mt19937 random_engine;
}  // namespace global

#endif  // GLOBAL_H
