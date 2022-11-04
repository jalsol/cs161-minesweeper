#include "utils.h"

#include <random>

#include "global.h"

std::random_device global::rd;
std::mt19937 global::random_engine{rd()};

int getRandomValue(int low, int high) {
    static std::uniform_int_distribution<int> distrib(low, high);
    return distrib(global::random_engine);
}

void DrawTextSus(const char* text, int pos_x, int pos_y, int font_size,
                 Color color) {
    static Font font =
        LoadFontEx("assets/Inyourfacejoffrey.ttf", 90, nullptr, 0);
    Vector2 pos_vec{static_cast<float>(pos_x), static_cast<float>(pos_y)};
    DrawTextEx(font, text, pos_vec, font_size, 1, color);
}
