#include <vector>
#include <cstdint>
#include <math.h>

#include "mapa.h"

CityMap::CityMap(int w, int h) : w(w), h(h), cells(w * h) {}

Cell& CityMap::at(int x, int y) {
    return cells[y * w + x];
}

bool CityMap::inside(int x, int y) const {
    return x >= 0 && y >= 0 && x < w && y < h;
}

CityMap createUniformGrid(int width, int height, float defaultLength){
    CityMap map(width, height);

    for (int y = 0; y < height; ++y){
        for (int x = 0; x < width; ++x){
            Cell& current = map.at(x, y);
            current.road = true;

            for(int d  = 0; d < 4; ++d){
                int nx = x + dx[d];
                int ny = y + dy[d];


                Edge& e = current.edge[d];
                e.baseLength = defaultLength;
                e.roadworks = 0.0f;
                e.cars = 0;
                e.capacity = 5;

                e.blocked = !map.inside(nx, ny);

            }
        }
    }
    return map;
}

float travelCost(const Edge& e){
    if (e.blocked || e.capacity <= 0) return INFINITY;
    float congestion = 1.0f;
    if (e.cars > e.capacity)
        congestion += 0.5f * (e.cars - e.capacity);
    return (e.baseLength + e.roadworks) * congestion;
}