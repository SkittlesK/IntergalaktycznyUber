#include "client.h"
#include "Pathfinding.h"
#include <limits>

std::vector<Client> generateClients(CityMap& map, int count, std::mt19937& rng) {
    std::vector<Client> clients;

    std::vector<int> roads;
    for (int y = 0; y < map.h; ++y)
        for (int x = 0; x < map.w; ++x)
            if (map.at(x, y).road) roads.push_back(y * map.w + x);

    if (roads.size() < 2) return clients;

    std::uniform_int_distribution<size_t> pick(0, roads.size() - 1);
    const float INF = std::numeric_limits<double>::infinity();

    int attempts = 0;
    const int maxAttempts = count * 20;

    while ((int)clients.size() < count && attempts++ < maxAttempts) {
        int s = roads[pick(rng)];
        int d = roads[pick(rng)];
        if (s == d) continue;

        auto r = Dijkstra::dijkstra(map, s % map.w, s / map.w);
        if (r.dist[d] == INF) continue;

        Client c;
        c.id = static_cast<int>(clients.size());
        c.spawn = s;
        c.dest = d;
        clients.push_back(c);
    }

    return clients;
}