#ifndef SCREEN_H
#define SCREEN_H

enum class ScreenType {
    Menu,
    Gameplay,
    Settings,
};

namespace global {

void screenToMenu();
void screenToGameplay();
void screenToContinue();
void screenToSettings();
ScreenType getScreenType();

}  // namespace global

#endif  // SCREEN_H
