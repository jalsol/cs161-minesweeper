#ifndef MENU_SCREEN_H
#define MENU_SCREEN_H

namespace menuScreen {
constexpr int play_corner_x = 95;
constexpr int play_corner_y = 390;

constexpr int settings_corner_x = 95;
constexpr int settings_corner_y = 495;

constexpr int button_width = 230;
constexpr int button_height = 100;

void interact();
void draw();
}  // namespace menuScreen

#endif  // MENU_SCREEN_H
