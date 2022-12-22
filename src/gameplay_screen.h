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

namespace gameplayScreen {

void interact();
void draw();
void startNewGame();
void loadOldGame();
void saveOldGame();
void saveHighScore();
void loadHighScore();

namespace internal {

extern Table table;
extern GameState game_state;
extern int time_elapsed;
extern int frame_counter;
extern double score;
extern double high_score;

void updateFrameCount();
std::array<int, 3> getCurrentTime();

}  // namespace internal
}  // namespace gameplayScreen

#endif  // GAMEPLAY_SCREEN_H
