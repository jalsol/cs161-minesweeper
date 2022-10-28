#include "utils.h"

#include <random>

#include "global.h"

std::random_device global::rd;
std::mt19937 global::random_engine{rd()};

int getRandomValue(int low, int high) {
    static std::uniform_int_distribution<int> distrib(low, high);
    return distrib(global::random_engine);
}
