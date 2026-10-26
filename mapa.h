#pragma once
#include <vector>

enum Dir { UP, DOWN, LEFT, RIGHT };

inline constexpr int dx[4] = {0, 0, -1, 1};
inline constexpr int dy[4] = {-1, 1, 0, 0};

struct Edge {
    float baseLength = 1.0f;
    float roadworks = 0.0f;
    bool blocked = false;
    int cars = 0;
    int capacity = 5;
};

struct Cell {
    bool road = true;
    Edge edge[4];
};

struct CityMap {
    int w, h;
    std::vector<Cell> cells;

    CityMap(int w, int h);

    Cell& at(int x, int y);
    bool inside(int x, int y) const;
};

CityMap createUniformGrid(int width = 5, int height = 5, float defaultLength = 1.0f);


#ifndef INTERGALAKTYCZNYUBER_MAPA_H
#define INTERGALAKTYCZNYUBER_MAPA_H

#endif //INTERGALAKTYCZNYUBER_MAPA_H