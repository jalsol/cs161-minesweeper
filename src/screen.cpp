#include "screen.h"

#include "gameplay_screen.h"

namespace global {
static ScreenType screen_type = ScreenType::Menu;

void screenToMenu() { screen_type = ScreenType::Menu; }

void screenToGameplay() {
    screen_type = ScreenType::Gameplay;
    GameplayScreen::startNewGame();
}

void screenToContinue() {
    screen_type = ScreenType::Gameplay;
    GameplayScreen::loadOldGame();
}

void screenToSettings() { screen_type = ScreenType::Settings; }

ScreenType getScreenType() { return screen_type; }

}  // namespace global
