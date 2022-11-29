#include "gameplay_screen.h"

#include <fstream>

#include "config.h"
#include "globals.h"
#include "raygui.h"
#include "raylib.h"
#include "screen.h"
#include "utils.h"

Table GameplayScreen::table;
GameState GameplayScreen::game_state;
int GameplayScreen::time_elapsed;
int GameplayScreen::frame_counter;
double GameplayScreen::score;
double GameplayScreen::high_score;

void GameplayScreen::interact() {
    if (game_state != GameState::Playing) {
        return;
    }

    const auto& [coord_x, coord_y] =
        table.getCoordsFromPos(GetMouseX(), GetMouseY());

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        int reveal_value = table.revealCell(coord_x, coord_y);

        if (reveal_value == -1) {
            game_state = GameState::Lost;
        } else if (reveal_value == 1) {
            game_state = GameState::Won;
            saveHighScore();
        }
    } else if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
        table.getCell(coord_x, coord_y).toggleFlag();
    }
}

void GameplayScreen::updateFrameCount() {
    if (game_state == GameState::Playing) {
        ++frame_counter;
    }

    if (frame_counter == global::frames_per_second) {
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

    const Config& config = Config::getConfigInstance();
    const auto& [hours, minutes, seconds] = getCurrentTime();
    score = config.number_of_bomb * table.getNumberOfRevealedCells() /
            double(config.table_width * config.table_height -
                   config.number_of_bomb);

    DrawTextSus(TextFormat("TIMER: %02d:%02d:%02d", hours, minutes, seconds),
                370, 30, font_size, WHITE);

    DrawTextSus(TextFormat("SCORE: %.3f", score), 550, 30, font_size, WHITE);

    DrawTextSus(TextFormat("HI-SCORE: %.3f", high_score), 700, 30, font_size,
                WHITE);

    bool save_game_selected =
        GuiButton(Rectangle({1111, 10, 170, 60}), "Save game");

    table.drawTable();

    if (save_game_selected && game_state == GameState::Playing) {
        saveOldGame();
    }

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
            DrawTextSus("Victory", 585, 555, 100, ORANGE);
        } break;
        case GameState::Lost: {
            static const Image lost_image = LoadImage("assets/amogus.png");
            static const Texture2D lost_texture =
                LoadTextureFromImage(lost_image);

            DrawRectangle(0, 0, 1366, 768, ColorAlpha(WHITE, 0.5));
            DrawTexture(lost_texture, 330, 0, WHITE);
            DrawTextSus("Defeat", 610, 555, 100, RED);
        } break;
        default:
            break;
    }

    bool new_game_selected =
        GuiButton(Rectangle({400, 650, 150, 100}), "New game");
    bool settings_selected =
        GuiButton(Rectangle({570, 650, 230, 100}), "Settings");
    bool menu_selected = GuiButton(Rectangle({820, 650, 130, 100}), "Menu");

    if (new_game_selected) {
        global::screenToGameplay();
    } else if (settings_selected) {
        global::screenToSettings();
    } else if (menu_selected) {
        global::screenToMenu();
    }
}

void GameplayScreen::startNewGame() {
    const Config& config = Config::getConfigInstance();

    table = Table(config.table_width, config.table_height);
    game_state = GameState::Playing;
    time_elapsed = 0;
    frame_counter = 0;
    score = 0;
}

void GameplayScreen::loadOldGame() {
    if (!std::ifstream("save.yaml")) {
        global::screenToMenu();
        return;
    }

    YAML::Node save_file = YAML::LoadFile("save.yaml");
    Config& config = Config::getConfigInstance();

    config.table_width = save_file["TableWidth"].as<int>();
    config.table_height = save_file["TableHeight"].as<int>();
    config.number_of_bomb = save_file["NumberOfBombs"].as<int>();

    time_elapsed = save_file["TimeElapsed"].as<int>();
    frame_counter = save_file["FrameSinceLastSecond"].as<int>();
    game_state = GameState::Playing;

    score = save_file["Score"].as<double>();
    std::string saved_table = save_file["Table"].as<std::string>();
    std::string saved_state = save_file["State"].as<std::string>();

    table = Table(config.table_width, config.table_height);
    table.loadFromSaveData(saved_table, saved_state);
}

void GameplayScreen::saveOldGame() {
    const Config& config = Config::getConfigInstance();
    YAML::Node node;

    std::string saved_table(table.getWidth() * table.getHeight(), '0');
    std::string saved_state(table.getWidth() * table.getHeight(), '0');

    for (int coord_y = 0; coord_y < table.getHeight(); ++coord_y) {
        for (int coord_x = 0; coord_x < table.getWidth(); ++coord_x) {
            const Cell& cell = table.getCell(coord_x, coord_y);
            int flattened_index = coord_y * table.getWidth() + coord_x;

            if (cell.getValue() == Cell::bomb_cell_value) {
                saved_table[flattened_index] = '*';
            } else {
                saved_table[flattened_index] = char(cell.getValue() + '0');
            }

            switch (cell.getCellState()) {
                case CellState::Opened: {
                    saved_state[flattened_index] = '1';
                } break;
                case CellState::Flagged: {
                    saved_state[flattened_index] = '!';
                } break;
                default: {
                    saved_state[flattened_index] = '0';
                } break;
            }
        }
    }

    node["TimeElapsed"] = time_elapsed;
    node["FrameSinceLastSecond"] = frame_counter;
    node["NumberOfRevealedCells"] = table.getNumberOfRevealedCells();
    node["Table"] = saved_table;
    node["State"] = saved_state;
    node["Score"] = score;

    std::ofstream save_file("save.yaml");
    save_file << config.config << '\n' << node;
    save_file.close();
}

void GameplayScreen::saveHighScore() {
    if (score > high_score) {
        high_score = score;

        std::ofstream saved_high_score("high_score.txt");
        saved_high_score << high_score;
        saved_high_score.close();
    }
}

void GameplayScreen::loadHighScore() {
    std::ifstream saved_high_score("high_score.txt");

    if (saved_high_score) {
        double high_score;
        saved_high_score >> high_score;
        saved_high_score.close();
    } else {
        saveHighScore();
    }

    saved_high_score.close();
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
