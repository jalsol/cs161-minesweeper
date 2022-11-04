#ifndef CELL_H
#define CELL_H

#include "raylib.h"

enum class CellState {
    Closed,
    Opened,
};

struct Cell {
public:
    static constexpr int sus_cell_value = -1;
    static constexpr int cell_size = 60;
    static constexpr int font_size = 30;

    Cell();
    ~Cell();

    void setValue(int value);
    int getValue() const;

    void setCellScreenPos(int x, int y);
    void drawCell();
    bool click();

private:
    int m_value;
    int m_screen_pos_x;
    int m_screen_pos_y;
    CellState m_cell_state;
};

#endif  // CELL_H
