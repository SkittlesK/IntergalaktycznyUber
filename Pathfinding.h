#pragma once
#include <vector>
#include "mapa.h"
#ifndef INTERGALAKTYCZNYUBER_PATHFINDING_H
#define INTERGALAKTYCZNYUBER_PATHFINDING_H

class Dijkstra {
public:
    struct DijkstraResult {
        std::vector<float> dist;
        std::vector<int> parent;
        int target = -1;
    };

    

    static DijkstraResult dijkstra(CityMap& map, int sx, int sy, bool reversed = false, const std::vector<char>& isTarget = {});

    static std::vector<int> buildPath(const DijkstraResult& r, int from);
};


#endif //INTERGALAKTYCZNYUBER_PATHFINDING_Hs