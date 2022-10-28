#include "table.h"

#include <algorithm>
#include <numeric>
#include <random>
#include <vector>

#include "global.h"
#include "utils.h"

Table::Table(int width, int height)
    : m_width(width), m_height(height), m_board(width * height) {
    fillTable();
}

Cell& Table::getCell(int x, int y) { return m_board.at(y * m_width + x); }

void Table::fillTable() {
    std::vector<int> flattened_indices(m_width * m_height);
    std::iota(flattened_indices.begin(), flattened_indices.end(), 0);

    for (int _ = 0; _ < 5; ++_) {
        std::shuffle(flattened_indices.begin(), flattened_indices.end(),
                     global::random_engine);
    }

    for (int i = 0; i < global::number_of_sus; ++i) {
        int pos_x = flattened_indices[i] % m_width;
        int pos_y = flattened_indices[i] / m_width;

        Cell& cell = getCell(pos_x, pos_y);
        cell.setValue(Cell::sus_cell_value);
    }

    for (int i = 0; i < m_width * m_height; ++i) {
        int pos_x = flattened_indices[i] % m_width;
        int pos_y = flattened_indices[i] / m_width;

        Cell& cell = getCell(pos_x, pos_y);

        if (cell.getValue() == Cell::sus_cell_value) {
            continue;
        }

        int nearby_sus_count = 0;

        for (int offset_x = -1; offset_x <= 1; ++offset_x) {
            for (int offset_y = -1; offset_y <= 1; ++offset_y) {
                if (offset_x == 0 && offset_y == 0) {
                    continue;
                }

                try {
                    Cell& nearby_cell =
                        getCell(pos_x + offset_x, pos_y + offset_y);

                    if (nearby_cell.getValue() == Cell::sus_cell_value) {
                        ++nearby_sus_count;
                    }
                } catch (...) {
                    // coordinates out of board's range
                }
            }
        }

        cell.setValue(nearby_sus_count);
    }
}
