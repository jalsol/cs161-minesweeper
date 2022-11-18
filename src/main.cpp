#include <iostream>

#include "gameplay_screen.h"
#include "menu_screen.h"
#include "raylib.h"
#include "screen.h"
#include "table.h"
#include "utils.h"

static constexpr int screen_width = 1366;
static constexpr int screen_height = 768;

int main() {
    constexpr int frames_per_second = 20;

    InitWindow(screen_width, screen_height,
               "Mongusweeper - a sussy Minesweeper clone by @jalsol");

    SetTargetFPS(frames_per_second);

    GameplayScreen::startNewGame();

    while (!WindowShouldClose()) {
        switch (global::getScreenType()) {
            case ScreenType::Menu: {
                MenuScreen::interact();
            } break;
            case ScreenType::Gameplay: {
                GameplayScreen::interact();
            } break;
            case ScreenType::Settings: {
                // SettingsScreen::interact();
            } break;
            default:
                break;
        }

        BeginDrawing();
        {
            switch (global::getScreenType()) {
                case ScreenType::Menu: {
                    MenuScreen::draw();
                } break;
                case ScreenType::Gameplay: {
                    GameplayScreen::draw();
                } break;
                case ScreenType::Settings: {
                    // SettingsScreen::draw();
                } break;
                default:
                    break;
            }
        }
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
