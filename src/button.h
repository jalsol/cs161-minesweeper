#ifndef BUTTON_H
#define BUTTON_H

#include <string>

#include "raylib.h"

struct Button {
public:
    Button(int pos_x, int pos_y, int width, int height, const std::string& text);

    void draw();
    bool isClicked(int mouse_x, int mouse_y);

private:
    int m_pos_x;
    int m_pos_y;
    int m_width;
    int m_height;
    const std::string m_text;
};

#endif  // BUTTON_H
