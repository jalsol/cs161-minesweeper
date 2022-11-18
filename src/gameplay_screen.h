#ifndef GAMEPLAY_SCREEN_H
#define GAMEPLAY_SCREEN_H

#include <array>

#include "table.h"

enum class GameState {
    Playing,
    Paused,
    Won,
    Lost,
};

struct GameplayScreen {
public:
    static void interact();
    static void draw();
    static void startNewGame();
    static void loadOldGame();
    static void saveOldGame();
    static void saveHighScore();
    static void loadHighScore();

private:
    static Table table;
    static GameState game_state;
    static int time_elapsed;
    static int frame_counter;
    static double score;
    static double high_score;

    static void updateFrameCount();
    static std::array<int, 3> getCurrentTime();
};

#endif  // GAMEPLAY_SCREEN_H
