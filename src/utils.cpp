#include "utils.h"

#include "raylib.h"

void DrawTextSus(const char* text, int pos_x, int pos_y, int font_size,
                 Color color) {
    static Font font =
        LoadFontEx("assets/Inyourfacejoffrey.ttf", 90, nullptr, 0);
    Vector2 pos_vec{static_cast<float>(pos_x), static_cast<float>(pos_y)};
    DrawTextEx(font, text, pos_vec, font_size, 1, color);
}
