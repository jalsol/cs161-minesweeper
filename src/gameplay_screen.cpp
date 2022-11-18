#include <iostream>

#include "button.h"
#include "raylib.h"
#include "screen.h"
#include "utils.h"

#include "gameplay_screen.h"

Table GameplayScreen::table;
GameState GameplayScreen::game_state;
int GameplayScreen::time_elapsed;
int GameplayScreen::frame_counter;
Button GameplayScreen::play_button(500, 570, 130, 100, "Play");
Button GameplayScreen::settings_button(650, 570, 230, 100, "Settings");

void GameplayScreen::interactGameEnd() {
    auto [mouse_x, mouse_y] = GetMousePosition();

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        if (play_button.isClicked(mouse_x, mouse_y)) {
            global::screenToGameplay();
            startNewGame();
        }
    }
}

void GameplayScreen::interact() {
    switch (game_state) {
        case GameState::Lost:
        case GameState::Won: {
            interactGameEnd();
            return;
        } break;
        default:
            break;
    }

    const auto& [coord_x, coord_y] = table.getCoordsFromPos(GetMouseX(), GetMouseY());

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

    switch (game_state) {
        case GameState::Paused: {
            DrawRectangle(0, 0, 1366, 768, WHITE);
        } break;
        case GameState::Won: {
            static const Image won_image = LoadImage("assets/amogus_drip.png");
            static const Texture2D won_texture =
                LoadTextureFromImage(won_image);

            DrawRectangle(0, 0, 1366, 768, ColorAlpha(WHITE, 0.5));
            DrawTexture(won_texture, 343, 20, WHITE);

            GameplayScreen::play_button.draw();
            GameplayScreen::settings_button.draw();
        } break;
        case GameState::Lost: {
            static const Image lost_image = LoadImage("assets/amogus.png");
            static const Texture2D lost_texture =
                LoadTextureFromImage(lost_image);

            DrawRectangle(0, 0, 1366, 768, ColorAlpha(WHITE, 0.5));
            DrawTexture(lost_texture, 330, 0, WHITE);

            GameplayScreen::play_button.draw();
            GameplayScreen::settings_button.draw();
        } break;
        default:
            break;
    }

    updateFrameCount();
}

void GameplayScreen::startNewGame() {
    table = Table(20, 10);
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
