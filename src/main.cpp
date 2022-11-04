#include <iostream>

#include "raylib.h"
#include "table.h"
#include "utils.h"

static constexpr int screen_width = 1366;
static constexpr int screen_height = 768;

int main() {
    static constexpr int frames_per_second = 20;

    InitWindow(screen_width, screen_height,
               "Mongusweeper - a sussy Minesweeper clone by jalsol");

    SetTargetFPS(frames_per_second);

    Table table(20, 10);

    while (!WindowShouldClose()) {
        static constexpr const char background_path[] = "assets/background.png";
        static const Image background_image = LoadImage(background_path);
        static const Texture2D background_texture =
            LoadTextureFromImage(background_image);
        static constexpr int font_size = 30;

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            auto [coord_x, coord_y] =
                table.getCoordsFromPos(GetMouseX(), GetMouseY());
            if (table.clickOnCell(coord_x, coord_y)) {
                std::cout << "amongus'd\n";
            }
        }

        BeginDrawing();
        {
            DrawTexture(background_texture, 0, 0, WHITE);

            DrawTextSus(TextFormat("SCORE: %i", 6969), 400, 30, font_size,
                        WHITE);
            DrawTextSus(TextFormat("TIMER: %i", 696969), 600, 30, font_size,
                        WHITE);
            DrawTextSus(TextFormat("BOMBS: %i", 69696969), 800, 30, font_size,
                        WHITE);

            table.drawTable();
        }
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
