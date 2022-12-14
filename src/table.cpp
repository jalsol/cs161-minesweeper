#include "table.h"

#include <algorithm>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <utility>
#include <vector>

#include "cell.h"
#include "config.h"
#include "utils.h"

Table::Table() : m_width(0), m_height(0), m_cells_revealed(0) {}

Table::Table(int width, int height)
    : m_width(width),
      m_height(height),
      m_board(width * height),
      m_cells_revealed(0) {
    fillTable();
    initCellsScreenPos();
}

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

std::pair<int, int> Table::getCoordsFromPos(double pos_x, double pos_y) {
    if (pos_x < corner_x || pos_y < corner_y) {
        return {-1, -1};
    }

    int coord_x = (pos_x - center_x) / Cell::cell_size + m_width / 2.0;
    int coord_y = (pos_y - center_y) / Cell::cell_size + m_height / 2.0;
    return {coord_x, coord_y};
}

std::pair<double, double> Table::getPosFromCoords(int coord_x, int coord_y) {
    double pos_x = center_x + (coord_x - m_width / 2.0) * Cell::cell_size;
    double pos_y = center_y + (coord_y - m_height / 2.0) * Cell::cell_size;
    return {pos_x, pos_y};
}

// returns -1 if clicked on bomb
// returns 1 if all non-bomb cells are cleared
// returns 0 otherwise
int Table::revealCell(int coord_x, int coord_y) {
    if (!coordsInRange(coord_x, coord_y)) {
        return 0;
    }

    Cell& cell = getCell(coord_x, coord_y);
    if (cell.getCellState() == CellState::Flagged) {
        return 0;
    }
    if (cell.getCellState() == CellState::Opened) {
        return 0;
    }

    bool clicked_on_bomb = cell.reveal();
    ++m_cells_revealed;

    if (clicked_on_bomb) {
        for (const auto& [bomb_coord_x, bomb_coord_y] : m_bomb_cell_coords) {
            getCell(bomb_coord_x, bomb_coord_y).reveal();
        }
        return -1;
    }

    if (cell.getValue() == 0) {
        clearNearbyCells(coord_x, coord_y);
    }

    const Config& config = Config::getConfigInstance();

    if (m_cells_revealed == m_width * m_height - config.number_of_bomb) {
        return 1;
    }

    return 0;
}

bool Table::coordsInRange(int coord_x, int coord_y) {
    return (0 <= coord_x && coord_x < m_width) &&
           (0 <= coord_y && coord_y < m_height);
}

void Table::fillTable() {
    std::vector<int> flattened_indices(m_width * m_height);
    std::iota(flattened_indices.begin(), flattened_indices.end(), 0);

    static std::random_device rd;
    static std::mt19937 random_engine{rd()};

    for (int _ = 0; _ < 5; ++_) {
        std::shuffle(flattened_indices.begin(), flattened_indices.end(),
                     random_engine);
    }

    const Config& config = Config::getConfigInstance();

    for (int i = 0; i < config.number_of_bomb; ++i) {
        int coord_x = flattened_indices[i] % m_width;
        int coord_y = flattened_indices[i] / m_width;
        m_bomb_cell_coords.emplace_back(coord_x, coord_y);

        Cell& cell = getCell(coord_x, coord_y);
        cell.setValue(Cell::bomb_cell_value);
    }

    for (int i = 0; i < m_width * m_height; ++i) {
        int coord_x = flattened_indices[i] % m_width;
        int coord_y = flattened_indices[i] / m_width;

        Cell& cell = getCell(coord_x, coord_y);

        if (cell.getValue() == Cell::bomb_cell_value) {
            continue;
        }

        int nearby_bomb_count = 0;

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

                if (nearby_cell.getValue() == Cell::bomb_cell_value) {
                    ++nearby_bomb_count;
                }
            }
        }

        cell.setValue(nearby_bomb_count);
    }
}

void Table::initCellsScreenPos() {
    for (int coord_y = 0; coord_y < m_height; ++coord_y) {
        for (int coord_x = 0; coord_x < m_width; ++coord_x) {
            Cell& cell = getCell(coord_x, coord_y);

            const auto& [pos_x, pos_y] = getPosFromCoords(coord_x, coord_y);
            cell.setCellScreenPos(pos_x, pos_y);
        }
    }
}

void Table::clearNearbyCells(int src_coord_x, int src_coord_y) {
    std::queue<std::pair<int, int>> queue;
    std::set<std::pair<int, int>> visited;

    queue.emplace(src_coord_x, src_coord_y);
    visited.emplace(src_coord_x, src_coord_y);

    while (!queue.empty()) {
        auto [coord_x, coord_y] = queue.front();
        queue.pop();

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

                if (nearby_cell_value == Cell::bomb_cell_value) {
                    continue;
                }

                if (nearby_cell.getCellState() != CellState::Opened) {
                    nearby_cell.reveal();
                    ++m_cells_revealed;
                }

                if (nearby_cell_value == 0) {
                    queue.emplace(nearby_x, nearby_y);
                    visited.emplace(nearby_x, nearby_y);
                }
            }
        }
    }
}

void Table::loadFromSaveData(const std::string& table,
                             const std::string& state) {
    for (int i = 0; i < m_width * m_height; ++i) {
        int coord_x = i % m_width;
        int coord_y = i / m_width;

        Cell& cell = getCell(coord_x, coord_y);

        switch (table[i]) {
            case '*': {
                cell.setValue(Cell::bomb_cell_value);
            } break;
            default: {
                cell.setValue(int(table[i] - '0'));
            } break;
        }

        switch (state[i]) {
            case '1': {
                cell.reveal();
                ++m_cells_revealed;
            } break;
            case '!': {
                cell.toggleFlag();
            } break;
        }
    }
}

int Table::getNumberOfRevealedCells() const { return m_cells_revealed; }
