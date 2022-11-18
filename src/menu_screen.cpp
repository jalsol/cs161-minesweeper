#include "menu_screen.h"

#include "gameplay_screen.h"
#include "raygui.h"
#include "raylib.h"
#include "screen.h"
#include "utils.h"

void MenuScreen::interact() {}

void MenuScreen::draw() {
    static const Image background_image = LoadImage("assets/menu_bg.png");
    static const Texture2D background_texture =
        LoadTextureFromImage(background_image);

    DrawTexture(background_texture, 0, 0, WHITE);
    DrawTextSus("Mongusweeper", 100, 100, 100, WHITE);

    bool play_selected = GuiButton(Rectangle({95, 390, 230, 100}), "Play");
    bool settings_selected =
        GuiButton(Rectangle({95, 495, 230, 100}), "Settings");

    if (play_selected) {
        global::screenToGameplay();
    } else if (settings_selected) {
        global::screenToSettings();
    }
}
