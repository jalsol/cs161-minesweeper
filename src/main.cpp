#include "raylib.h"

int main() {
    constexpr int screen_width = 800;
    constexpr int screen_height = 450;
    constexpr int frames_per_second = 60;

    InitWindow(screen_width, screen_height, "not sus at all window");

    SetTargetFPS(frames_per_second);

    constexpr int pos_x = 250;
    constexpr int pos_y = 200;
    constexpr int font_size = 20;

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText("so this is a window, huh", pos_x, pos_y, font_size, BLACK);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
