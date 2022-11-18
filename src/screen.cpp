#include "screen.h"

namespace global {
static ScreenType screen_type = ScreenType::Menu;

void screenToMenu() { screen_type = ScreenType::Menu; }

void screenToGameplay() { screen_type = ScreenType::Gameplay; }

void screenToSettings() { screen_type = ScreenType::Settings; }

ScreenType getScreenType() { return screen_type; }

}  // namespace global
