#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "gameplay_screen.h"
#include "globals.h"
#include "menu_screen.h"
#include "raygui.h"
#include "screen.h"
#include "settings_screen.h"
#include "table.h"
#include "utils.h"

int main() {
    InitWindow(global::screen_width, global::screen_height,
               "Mongusweeper - a sussy Minesweeper clone by @jalsol");

    SetTargetFPS(global::frames_per_second);

    // Load music
    static Music menu_theme;
    {
        InitAudioDevice();
        menu_theme = LoadMusicStream("assets/theme.mp3");
        PlayMusicStream(menu_theme);
    }

    // load icon
    {
        static Image icon = LoadImage("assets/logo.png");
        ImageFormat(&icon, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
        SetWindowIcon(icon);
        UnloadImage(icon);
    }

    // load font and set style for buttons
    {
        static Font font =
            LoadFontEx("assets/Inyourfacejoffrey.ttf", 90, nullptr, 0);
        GuiSetFont(font);
        GuiSetStyle(DEFAULT, TEXT_SIZE, 50);
        GuiSetStyle(SPINNER, SPIN_BUTTON_WIDTH, 60);
    }

    while (!WindowShouldClose()) {
        UpdateMusicStream(menu_theme);

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
