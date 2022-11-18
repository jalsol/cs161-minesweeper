#include "button.h"

#include "raylib.h"
#include "utils.h"

Button::Button(int pos_x, int pos_y, int width, int height, const std::string& text)
    : m_pos_x(pos_x),
      m_pos_y(pos_y),
      m_width(width),
      m_height(height),
      m_text(text) {}

void Button::draw() {
    DrawRectangle(m_pos_x, m_pos_y, m_width, m_height, ColorAlpha(GRAY, 0.7));
    DrawRectangleLines(m_pos_x, m_pos_y, m_width, m_height, GRAY);
    DrawTextSus(m_text.c_str(), m_pos_x + 5, m_pos_y + 5, 100, RED);
}

bool Button::isClicked(int mouse_x, int mouse_y) {
    return (m_pos_x <= mouse_x && mouse_x < m_pos_x + m_width) &&
           (m_pos_y <= mouse_y && mouse_y < m_pos_y + m_height);
}
