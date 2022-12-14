#include "settings_screen.h"

#include "config.h"
#include "gameplay_screen.h"
#include "globals.h"
#include "raygui.h"
#include "raylib.h"
#include "screen.h"
#include "utils.h"

namespace settingsScreen {

void draw() {
    static const Image background_image = LoadImage("assets/menu_bg.png");
    static const Texture2D background_texture =
        LoadTextureFromImage(background_image);

    DrawTexture(background_texture, 0, 0, WHITE);
    DrawTextSus("Settings", 100, 100, 100, WHITE);

    Config& config = Config::getConfigInstance();

    if (GuiButton(Rectangle({400, 200, global::screen_width - 400 * 2, 80}),
                  "Save and Return to Menu")) {
        config.writeConfig();
        global::screenToMenu();
    }

    GuiSpinner(Rectangle({400, 310, global::screen_width - 400 * 2, 80}),
               "width ", &config.table_width, 3, 20, false);
    GuiSpinner(Rectangle({400, 400, global::screen_width - 400 * 2, 80}),
               "height ", &config.table_height, 3, 10, false);
    GuiSpinner(Rectangle({400, 490, global::screen_width - 400 * 2, 80}),
               "bombs ", &config.number_of_bomb, 1,
               config.table_width * config.table_height, false);
}

void interact() {}

}  // namespace settingsScreen
