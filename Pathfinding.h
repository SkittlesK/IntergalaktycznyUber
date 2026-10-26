#pragma once
#include <vector>
#include "mapa.h"
class Dijkstra {
    struct DijkstraResult {
        std::vector<float> dist;
        std::vector<int> parent;
        int target = -1;
    };

    float edgeCost(const Edge& e);

    DijkstraResult dijkstra(CityMap& map, int sx, int sy, bool reversed = false, const std::vector<char>& isTarget = {});

    std::vector<int> buildPath(const DijkstraResult& r, int from);
}

#ifndef INTERGALAKTYCZNYUBER_PATHFINDING_H
#define INTERGALAKTYCZNYUBER_PATHFINDING_H

#endif //INTERGALAKTYCZNYUBER_PATHFINDING_H