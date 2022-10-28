#ifndef TABLE_H
#define TABLE_H

#include <vector>

#include "cell.h"

struct Table {
public:
    Table(int width, int height);
    ~Table();

    Cell& getCell(int x, int y);

private:
    int m_width;
    int m_height;
    std::vector<Cell> m_board;

    void fillTable();
};

#endif  // TABLE_H
