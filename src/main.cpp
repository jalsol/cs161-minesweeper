#include "constants.h"
#include "raylib.h"

int main() {
    InitWindow(screen_width, screen_height, "Minesuswepper");

    SetTargetFPS(frames_per_second);

    constexpr int pos_x = 250;
    constexpr int pos_y = 200;
    constexpr int font_size = 20;

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText("sussy baka", pos_x, pos_y, font_size, BLACK);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
