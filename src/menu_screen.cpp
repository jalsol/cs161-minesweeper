#include "menu_screen.h"

#include "gameplay_screen.h"
#include "raygui.h"
#include "raylib.h"
#include "screen.h"
#include "utils.h"

namespace menuScreen {

void draw() {
    static const Image background_image = LoadImage("assets/menu_bg.png");
    static const Texture2D background_texture =
        LoadTextureFromImage(background_image);

    DrawTexture(background_texture, 0, 0, WHITE);
    DrawTextSus("Mongusweeper", 100, 100, 100, WHITE);
    DrawTextSus("@jalsol", 100, 190, 30, WHITE);

    bool new_game_selected = GuiButton(
        Rectangle({play_corner_x, play_corner_y, button_width, button_height}),
        "New game");
    bool continue_selected =
        GuiButton(Rectangle({continue_corner_x, continue_corner_y, button_width,
                             button_height}),
                  "Continue");
    bool settings_selected =
        GuiButton(Rectangle({settings_corner_x, settings_corner_y, button_width,
                             button_height}),
                  "Settings");

    if (new_game_selected) {
        global::screenToGameplay();
    } else if (continue_selected) {
        global::screenToContinue();
    } else if (settings_selected) {
        global::screenToSettings();
    }
}

void interact() {}

}  // namespace menuScreen
