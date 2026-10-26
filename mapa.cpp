#include "mapa.h"
#include <vector>
#include <cstdint>

#include "mapa.h"

CityMap::CityMap(int w, int h) : w(w), h(h), cells(w * h) {}

Cell& CityMap::at(int x, int y) {
    return cells[y * w + x];
}

bool CityMap::inside(int x, int y) const {
    return x >= 0 && y >= 0 && x < w && y < h;
}