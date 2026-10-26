#include "Pathfinding.h"
#include <queue>
#include <limits>
#include <cmath>
#include <functional>

float edgeCost(const Edge& e) {
    if (e.blocked || e.capacity <= 0) return std::numeric_limits<float>::infinity();
    float load = static_cast<float>(e.cars) / e.capacity;
    return e.baseLength * (1.0f + 0.15f * std::pow(load, 4.0f)) + e.roadworks;
}

DijkstraResult dijkstra(CityMap& map, int sx, int sy, bool reversed, const std::vector<char>& isTarget) {
    // co co znaczy:              mapa normalnie, skądx, dokądx, czy na odwrot, to ma sens przy szukaniu 1 kierowcy
    const float INF = std::numeric_limits<float>::infinity();
    int n = map.w * map.h;

    DijkstraResult res;
    res.dist.assign(n, INF);
    res.parent.assign(n, -1);

    if (!map.inside(sx, sy) || !map.at(sx, sy).road) return res;

    using State = std::pair<float, int>;
    std::priority_queue<State, std::vector<State>, std::greater<State>> pq;

    int s = sy * map.w + sx;
    res.dist[s] = 0.0f;
    pq.push({0.0f, s});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (d > res.dist[u]) continue;

        if (!isTarget.empty() && isTarget[u]) {
            res.target = u;
            break;
        }

        int ux = u % map.w;
        int uy = u / map.w;

        for (int k = 0; k < 4; ++k) {
            int vx = ux + dx[k];
            int vy = uy + dy[k];

            if (!map.inside(vx, vy)) continue;

            Cell& vc = map.at(vx, vy);
            if (!vc.road) continue;

            const Edge& e = reversed ? vc.edge[k ^ 1] : map.at(ux, uy).edge[k];
            float nd = d + edgeCost(e);
            int v = vy * map.w + vx;

            if (nd < res.dist[v]) {
                res.dist[v] = nd;
                res.parent[v] = u;
                pq.push({nd, v});
            }
        }
    }

    return res;
}

std::vector<int> buildPath(const DijkstraResult& r, int from) {
    std::vector<int> path;
    if (r.dist[from] == std::numeric_limits<float>::infinity()) return path;
    for (int v = from; v != -1; v = r.parent[v]) path.push_back(v);
    return path;
}