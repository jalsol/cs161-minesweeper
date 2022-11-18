#ifndef CELL_H
#define CELL_H

#include "raylib.h"

enum class CellState {
    Closed,
    Opened,
    Flagged,
};

struct Cell {
public:
    static constexpr int bomb_cell_value = -1;
    static constexpr int cell_size = 60;
    static constexpr int font_size = 30;

    Cell();
    ~Cell();

    void setValue(int value);
    int getValue() const;

    void setCellScreenPos(int x, int y);
    void drawCell();
    bool reveal();
    void toggleFlag();
    CellState getCellState() const;

private:
    int m_value;
    double m_screen_pos_x;
    double m_screen_pos_y;
    CellState m_cell_state;
};

#endif  // CELL_H
