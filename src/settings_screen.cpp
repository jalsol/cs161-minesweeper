#include "settings_screen.h"

#include "config.h"
#include "gameplay_screen.h"
#include "raygui.h"
#include "raylib.h"
#include "screen.h"
#include "utils.h"

static constexpr int screen_width = 1366;
static constexpr int screen_height = 768;

void SettingsScreen::draw() {
    static const Image background_image = LoadImage("assets/menu_bg.png");
    static const Texture2D background_texture =
        LoadTextureFromImage(background_image);

    DrawTexture(background_texture, 0, 0, WHITE);
    DrawTextSus("Settings", 100, 100, 100, WHITE);

    Config& config = Config::getConfigInstance();

    if (GuiButton(Rectangle({400, 200, screen_width - 400 * 2, 80}), "SAVE")) {
        config.writeConfig();
        global::screenToMenu();
    }

    GuiSpinner(Rectangle({400, 310, screen_width - 400 * 2, 80}), "width ",
               &config.m_table_width, 3, 20, false);
    GuiSpinner(Rectangle({400, 400, screen_width - 400 * 2, 80}), "height ",
               &config.m_table_height, 3, 10, false);
    GuiSpinner(Rectangle({400, 490, screen_width - 400 * 2, 80}), "bombs ",
               &config.m_number_of_bomb, 1,
               config.m_table_width * config.m_table_height, false);
}

void SettingsScreen::interact() {}
