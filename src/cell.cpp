#include "cell.h"

Cell::Cell() : m_value(0) {}

Cell::~Cell() {}

void Cell::setValue(int value) { m_value = value; }

int Cell::getValue() { return m_value; }
