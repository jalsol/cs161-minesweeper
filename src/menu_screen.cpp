#include "menu_screen.h"

#include "button.h"
#include "raylib.h"
#include "screen.h"
#include "utils.h"

Button MenuScreen::play_button(95, 390, 230, 100, "Play");
Button MenuScreen::settings_button(95, 495, 230, 100, "Settings");

void MenuScreen::interact() {
    auto [mouse_x, mouse_y] = GetMousePosition();

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        if (play_button.isClicked(mouse_x, mouse_y)) {
            global::screenToGameplay();
        }
    }
}

void MenuScreen::draw() {
    static const Image background_image = LoadImage("assets/menu_bg.png");
    static const Texture2D background_texture =
        LoadTextureFromImage(background_image);

    DrawTexture(background_texture, 0, 0, WHITE);
    DrawTextSus("Mongusweeper", 100, 100, 100, WHITE);

    play_button.draw();
    settings_button.draw();
}
