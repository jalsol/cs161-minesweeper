#include "cell.h"

#include "raylib.h"

Cell::Cell()
    : m_value(0),
      m_screen_pos_x(0),
      m_screen_pos_y(0),
      m_cell_state(CellState::Closed) {}

void Cell::setValue(int value) { m_value = value; }

int Cell::getValue() const { return m_value; }

void Cell::setCellScreenPos(int x, int y) {
    m_screen_pos_x = x;
    m_screen_pos_y = y;
}

CellState Cell::getCellState() const { return m_cell_state; }

void Cell::drawCell() {
    static const Image closed_image = LoadImage("assets/vent.png");
    static const Image bomb_image = LoadImage("assets/sus.png");
    static const Image flag_image = LoadImage("assets/guess.png");

    static const Texture2D closed_texture = LoadTextureFromImage(closed_image);
    static const Texture2D bomb_texture = LoadTextureFromImage(bomb_image);
    static const Texture2D flag_texture = LoadTextureFromImage(flag_image);

    DrawRectangle(m_screen_pos_x, m_screen_pos_y, cell_size, cell_size,
                  ColorAlpha(WHITE, 0.5f));

    DrawRectangleLines(m_screen_pos_x, m_screen_pos_y, cell_size, cell_size,
                       ORANGE);

    switch (m_cell_state) {
        case CellState::Opened: {
            if (m_value == bomb_cell_value) {
                DrawTexture(bomb_texture, m_screen_pos_x, m_screen_pos_y,
                            WHITE);
            } else if (m_value > 0) {
                DrawText(TextFormat("%d", m_value),
                         m_screen_pos_x + cell_size / 2.0,
                         m_screen_pos_y + cell_size / 2.0, font_size, BLACK);
            }
        } break;
        case CellState::Closed: {
            DrawTexture(closed_texture, m_screen_pos_x, m_screen_pos_y, WHITE);
        } break;
        case CellState::Flagged: {
            DrawTexture(closed_texture, m_screen_pos_x, m_screen_pos_y, WHITE);
            DrawTexture(flag_texture, m_screen_pos_x, m_screen_pos_y, WHITE);
        } break;
    }
}

// returns true if clicked on bomb
bool Cell::reveal() {
    if (m_cell_state != CellState::Opened) {
        m_cell_state = CellState::Opened;
    }

    return m_value == bomb_cell_value;
}

void Cell::toggleFlag() {
    switch (m_cell_state) {
        case CellState::Closed: {
            m_cell_state = CellState::Flagged;
        } break;
        case CellState::Flagged: {
            m_cell_state = CellState::Closed;
        } break;
        default:
            break;
    }
}
