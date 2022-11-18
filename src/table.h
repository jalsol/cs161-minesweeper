#ifndef TABLE_H
#define TABLE_H

#include <utility>
#include <vector>

#include "cell.h"

struct Table {
public:
    static constexpr int corner_x = 83;
    static constexpr int corner_y = 80;

    Table();
    Table(int width, int height);
    ~Table();

    Cell& getCell(int x, int y);
    int getWidth() const;
    int getHeight() const;
    void drawTable();
    std::pair<int, int> getCoordsFromPos(int pos_x, int pos_y);
    std::pair<int, int> getPosFromCoords(int coord_x, int coord_y);
    int revealCell(int coord_x, int coord_y);
    bool coordsInRange(int coord_x, int coord_y);

    std::vector<std::pair<int, int>> m_bomb_cell_coords;

private:
    int m_width;
    int m_height;
    std::vector<Cell> m_board;
    int m_cells_revealed;

    void fillTable();
    void initCellsScreenPos();
    int clearNearbyCells(int coord_x, int coord_y);
};

#endif  // TABLE_H
