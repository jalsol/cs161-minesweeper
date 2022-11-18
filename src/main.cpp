#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "gameplay_screen.h"
#include "menu_screen.h"
#include "raygui.h"
#include "screen.h"
#include "settings_screen.h"
#include "table.h"
#include "utils.h"

static constexpr int screen_width = 1366;
static constexpr int screen_height = 768;

int main() {
    constexpr int frames_per_second = 20;

    InitWindow(screen_width, screen_height,
               "Mongusweeper - a sussy Minesweeper clone by @jalsol");

    SetTargetFPS(frames_per_second);

    static Font font =
        LoadFontEx("assets/Inyourfacejoffrey.ttf", 90, nullptr, 0);
    GuiSetFont(font);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 50);
    GuiSetStyle(SPINNER, SPIN_BUTTON_WIDTH, 60);

    while (!WindowShouldClose()) {
        switch (global::getScreenType()) {
            case ScreenType::Menu: {
                MenuScreen::interact();
            } break;
            case ScreenType::Gameplay: {
                GameplayScreen::interact();
            } break;
            case ScreenType::Settings: {
                SettingsScreen::interact();
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
                    SettingsScreen::draw();
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
