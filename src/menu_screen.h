#ifndef MENU_SCREEN_H
#define MENU_SCREEN_H

#include "button.h"

struct MenuScreen {
    static constexpr int play_corner_x = 95;
    static constexpr int play_corner_y = 390;

    static constexpr int settings_corner_x = 95;
    static constexpr int settings_corner_y = 495;

    static constexpr int button_width = 230;
    static constexpr int button_height = 100;

    static void interact();
    static void draw();

private:
    static Button play_button;
    static Button settings_button;
};

#endif  // MENU_SCREEN_H
