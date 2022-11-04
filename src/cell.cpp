#include "cell.h"

#include "raylib.h"

Cell::Cell()
    : m_value(0),
      m_screen_pos_x(0),
      m_screen_pos_y(0),
      m_cell_state(CellState::Closed) {}

Cell::~Cell() {}

void Cell::setValue(int value) { m_value = value; }

int Cell::getValue() const { return m_value; }

void Cell::setCellScreenPos(int x, int y) {
    m_screen_pos_x = x;
    m_screen_pos_y = y;
}

void Cell::drawCell() {
    static constexpr const char vent_image_path[] = "assets/vent.png";
    static constexpr const char sus_image_path[] = "assets/sus.png";

    static const Image vent_image = LoadImage(vent_image_path);
    static const Image sus_image = LoadImage(sus_image_path);

    static const Texture2D vent_texture = LoadTextureFromImage(vent_image);
    static const Texture2D sus_texture = LoadTextureFromImage(sus_image);

    DrawRectangle(m_screen_pos_x, m_screen_pos_y, cell_size, cell_size,
                  ColorAlpha(WHITE, 0.5f));

    DrawRectangleLines(m_screen_pos_x, m_screen_pos_y, cell_size, cell_size,
                       ORANGE);

    switch (m_cell_state) {
        case CellState::Opened: {
            if (m_value == sus_cell_value) {
                DrawTexture(sus_texture, m_screen_pos_x, m_screen_pos_y, WHITE);
            } else if (m_value > 0) {
                DrawText(TextFormat("%d", m_value),
                         m_screen_pos_x + cell_size / 2,
                         m_screen_pos_y + cell_size / 2, font_size, BLACK);
            }
        } break;
        case CellState::Closed: {
            DrawTexture(vent_texture, m_screen_pos_x, m_screen_pos_y, WHITE);
        } break;
    }
}

// returns true if clicked on bomb
bool Cell::click() {
    m_cell_state = CellState::Opened;
    return m_value == sus_cell_value;
}
