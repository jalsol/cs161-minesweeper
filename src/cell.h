#ifndef CELL_H
#define CELL_H

#include <string_view>

enum class CellState {
    Closed,
    Opened,
};

struct Cell {
public:
    static constexpr int sus_cell_value = -1;
    static constexpr std::string_view closed_texture = "something";
    static constexpr std::string_view opened_texture = "something";

    Cell();
    ~Cell();

    void setValue(int value);
    int getValue() const;

private:
    int m_value;
};

#endif  // CELL_H
