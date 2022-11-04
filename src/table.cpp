#include "table.h"

#include <algorithm>
#include <iostream>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <utility>
#include <vector>

#include "cell.h"
#include "config.h"
#include "global.h"
#include "utils.h"

Table::Table(int width, int height)
    : m_width(width), m_height(height), m_board(width * height) {
    fillTable();
    initCellsScreenPos();
}

Table::~Table() {}

Cell& Table::getCell(int x, int y) { return m_board.at(y * m_width + x); }

int Table::getWidth() const { return m_width; }

int Table::getHeight() const { return m_height; }

void Table::drawTable() {
    for (int coord_y = 0; coord_y < m_height; ++coord_y) {
        for (int coord_x = 0; coord_x < m_width; ++coord_x) {
            getCell(coord_x, coord_y).drawCell();
        }
    }
}

std::pair<int, int> Table::getCoordsFromPos(int pos_x, int pos_y) {
    int coord_x = (pos_x - corner_x) / Cell::cell_size;
    int coord_y = (pos_y - corner_y) / Cell::cell_size;
    return {coord_x, coord_y};
}

std::pair<int, int> Table::getPosFromCoords(int coord_x, int coord_y) {
    int pos_x = corner_x + coord_x * Cell::cell_size;
    int pos_y = corner_y + coord_y * Cell::cell_size;
    return {pos_x, pos_y};
}

// returns false if got amongus'd
bool Table::clickOnCell(int coord_x, int coord_y) {
    if (!coordsInRange(coord_x, coord_y)) {
        return true;
    }

    Cell& cell = getCell(coord_x, coord_y);
    bool clicked_on_sus = cell.click();

    if (clicked_on_sus) {
        std::cout << "liem 2 hon dai tao\n";

        for (const auto& [sus_coord_x, sus_coord_y] : m_sus_cell_coords) {
            getCell(sus_coord_x, sus_coord_y).click();
        }

        return false;
    }

    if (cell.getValue() == 0) {
        clearNearbyCells(coord_x, coord_y);
    }

    return true;
}

bool Table::coordsInRange(int coord_x, int coord_y) {
    return (0 <= coord_x && coord_x < m_width) &&
           (0 <= coord_y && coord_y < m_height);
}

void Table::fillTable() {
    std::vector<int> flattened_indices(m_width * m_height);
    std::iota(flattened_indices.begin(), flattened_indices.end(), 0);

    for (int _ = 0; _ < 5; ++_) {
        std::shuffle(flattened_indices.begin(), flattened_indices.end(),
                     global::random_engine);
    }

    // const Config& config = Config::getConfigInstance();

    for (int i = 0; i < 20; ++i) {
        int coord_x = flattened_indices[i] % m_width;
        int coord_y = flattened_indices[i] / m_width;
        m_sus_cell_coords.emplace_back(coord_x, coord_y);

        Cell& cell = getCell(coord_x, coord_y);
        cell.setValue(Cell::sus_cell_value);
    }

    for (int i = 0; i < m_width * m_height; ++i) {
        int coord_x = flattened_indices[i] % m_width;
        int coord_y = flattened_indices[i] / m_width;

        Cell& cell = getCell(coord_x, coord_y);

        if (cell.getValue() == Cell::sus_cell_value) {
            continue;
        }

        int nearby_sus_count = 0;

        for (int offset_x = -1; offset_x <= 1; ++offset_x) {
            for (int offset_y = -1; offset_y <= 1; ++offset_y) {
                if (offset_x == 0 && offset_y == 0) {
                    // no offset at all -> not nearby cell
                    continue;
                }

                int nearby_x = coord_x + offset_x;
                int nearby_y = coord_y + offset_y;

                if (!coordsInRange(nearby_x, nearby_y)) {
                    continue;
                }

                const Cell& nearby_cell = getCell(nearby_x, nearby_y);

                if (nearby_cell.getValue() == Cell::sus_cell_value) {
                    ++nearby_sus_count;
                }
            }
        }

        cell.setValue(nearby_sus_count);
    }
}

void Table::initCellsScreenPos() {
    for (int coord_y = 0; coord_y < m_height; ++coord_y) {
        for (int coord_x = 0; coord_x < m_width; ++coord_x) {
            Cell& cell = getCell(coord_x, coord_y);

            auto [pos_x, pos_y] = getPosFromCoords(coord_x, coord_y);
            cell.setCellScreenPos(pos_x, pos_y);
        }
    }
}

void Table::clearNearbyCells(int src_coord_x, int src_coord_y) {
    std::queue<std::pair<int, int>> queue;
    std::set<std::pair<int, int>> visited;

    queue.emplace(src_coord_x, src_coord_y);

    while (!queue.empty()) {
        auto [coord_x, coord_y] = queue.front();
        queue.pop();
        visited.emplace(coord_x, coord_y);

        for (int offset_x = -1; offset_x <= 1; ++offset_x) {
            for (int offset_y = -1; offset_y <= 1; ++offset_y) {
                if (offset_x == 0 && offset_y == 0) {
                    continue;
                }

                int nearby_x = coord_x + offset_x;
                int nearby_y = coord_y + offset_y;

                if (!coordsInRange(nearby_x, nearby_y)) {
                    continue;
                }

                if (visited.contains({nearby_x, nearby_y})) {
                    continue;
                }

                Cell& nearby_cell = getCell(nearby_x, nearby_y);
                int nearby_cell_value = nearby_cell.getValue();

                if (nearby_cell_value == Cell::sus_cell_value) {
                    continue;
                }

                nearby_cell.click();

                if (nearby_cell_value == 0) {
                    queue.emplace(nearby_x, nearby_y);
                }
            }
        }
    }
}
