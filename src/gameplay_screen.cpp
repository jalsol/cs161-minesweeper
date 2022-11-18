#include "gameplay_screen.h"

#include <iostream>

#include "config.h"
#include "raygui.h"
#include "raylib.h"
#include "screen.h"
#include "utils.h"

Table GameplayScreen::table;
GameState GameplayScreen::game_state;
int GameplayScreen::time_elapsed;
int GameplayScreen::frame_counter;

void GameplayScreen::interact() {
    const auto& [coord_x, coord_y] =
        table.getCoordsFromPos(GetMouseX(), GetMouseY());

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        int reveal_value = table.revealCell(coord_x, coord_y);

        if (reveal_value == -1) {
            game_state = GameState::Lost;
        } else if (reveal_value == 1) {
            game_state = GameState::Won;
        }
    } else if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
        table.getCell(coord_x, coord_y).toggleFlag();
    }
}

void GameplayScreen::updateFrameCount() {
    if (game_state == GameState::Playing) {
        ++frame_counter;
    }

    if (frame_counter == 20) {
        frame_counter = 0;
        ++time_elapsed;
    }
}

void GameplayScreen::draw() {
    static const Image background_image = LoadImage("assets/background.png");
    static const Texture2D background_texture =
        LoadTextureFromImage(background_image);
    static constexpr int font_size = 30;

    DrawTexture(background_texture, 0, 0, WHITE);

    const auto& [hours, minutes, seconds] = getCurrentTime();

    DrawTextSus(TextFormat("TIMER: %02d:%02d:%02d", hours, minutes, seconds),
                600, 30, font_size, WHITE);
    // DrawTextSus(TextFormat("BOMBS: %d", 6969), 800, 30, font_size, WHITE);

    table.drawTable();

    if (game_state == GameState::Playing) {
        updateFrameCount();
        return;
    }

    switch (game_state) {
        case GameState::Won: {
            static const Image won_image = LoadImage("assets/amogus_drip.png");
            static const Texture2D won_texture =
                LoadTextureFromImage(won_image);

            DrawRectangle(0, 0, 1366, 768, ColorAlpha(WHITE, 0.5));
            DrawTexture(won_texture, 343, 20, WHITE);
        } break;
        case GameState::Lost: {
            static const Image lost_image = LoadImage("assets/amogus.png");
            static const Texture2D lost_texture =
                LoadTextureFromImage(lost_image);

            DrawRectangle(0, 0, 1366, 768, ColorAlpha(WHITE, 0.5));
            DrawTexture(lost_texture, 330, 0, WHITE);
        } break;
        default:
            break;
    }

    float a = 420;

    bool play_selected = GuiButton(Rectangle({a, 570, 130, 100}), "Play");
    bool settings_selected =
        GuiButton(Rectangle({a + 150, 570, 230, 100}), "Settings");
    bool menu_selected =
        GuiButton(Rectangle({a + 150 + 230 + 20, 570, 130, 100}), "Menu");

    if (play_selected) {
        global::screenToGameplay();
    } else if (settings_selected) {
        global::screenToSettings();
    } else if (menu_selected) {
        global::screenToMenu();
    }
}

void GameplayScreen::startNewGame() {
    const Config& config = Config::getConfigInstance();

    table = Table(config.getTableWidth(), config.getTableHeight());
    game_state = GameState::Playing;
    time_elapsed = 0;
    frame_counter = 0;
}

std::array<int, 3> GameplayScreen::getCurrentTime() {
    // duration is a copy
    int duration = time_elapsed;

    int seconds = duration % 60;
    duration /= 60;

    int minutes = duration % 60;
    duration /= 60;

    // duration is now hours

    return {duration /* hours */, minutes, seconds};
}
