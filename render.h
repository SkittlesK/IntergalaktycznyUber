#ifndef INTERGALAKTYCZNYUBER_RENDER_H
#define INTERGALAKTYCZNYUBER_RENDER_H

#include <vector>
#include "mapa.h"

struct RenderData {
    std::vector<int> path;
    std::vector<int> drivers;
    int client = -1;
};

void render(CityMap& map, const RenderData& data = {});

#endif //INTERGALAKTYCZNYUBER_RENDER_H