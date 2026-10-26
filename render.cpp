#include "render.h"
#include <algorithm>
#include <iostream>
#include <set>
#include <string>

namespace {

const std::string RESET = "\033[0m";
const std::string BOLD = "\033[1m";
const std::string RED = "\033[31m";
const std::string GREEN = "\033[32m";
const std::string YELLOW = "\033[33m";
const std::string MAGENTA = "\033[35m";
const std::string CYAN = "\033[36m";

struct Link {
    bool exists = false;
    bool blocked = false;
    bool works = false;
    float load = 0.0f;
};

float loadOf(const Edge& e) {
    if (e.capacity <= 0) return 1.0f;
    return static_cast<float>(e.cars) / e.capacity;
}

Link linkBetween(CityMap& map, int x, int y, int k) {
    Link l;
    int nx = x + dx[k];
    int ny = y + dy[k];
    if (!map.inside(nx, ny)) return l;

    Cell& a = map.at(x, y);
    Cell& b = map.at(nx, ny);
    if (!a.road || !b.road) return l;

    const Edge& ab = a.edge[k];
    const Edge& ba = b.edge[k ^ 1];

    l.exists = true;
    l.blocked = ab.blocked || ba.blocked;
    l.works = ab.roadworks > 0.0f || ba.roadworks > 0.0f;
    l.load = std::max(loadOf(ab), loadOf(ba));
    return l;
}

std::string linkColor(const Link& l, bool onPath) {
    if (onPath) return BOLD + CYAN;
    if (l.blocked) return RED;
    if (l.works) return MAGENTA;
    if (l.load >= 1.0f) return RED;
    if (l.load >= 0.6f) return YELLOW;
    return GREEN;
}

std::string horizontalLink(const Link& l, bool onPath) {
    if (!l.exists) return "   ";
    char side = onPath ? '=' : '-';
    char mid = onPath ? '=' : l.blocked ? 'X' : l.works ? 'R' : '-';
    std::string s;
    s += side;
    s += mid;
    s += side;
    return linkColor(l, onPath) + s + RESET;
}

std::string verticalLink(const Link& l, bool onPath) {
    if (!l.exists) return " ";
    char c = onPath ? '#' : l.blocked ? 'X' : l.works ? 'R' : '|';
    return linkColor(l, onPath) + std::string(1, c) + RESET;
}

std::string nodeSymbol(const Cell& cell, int i, const RenderData& data,
                       const std::vector<char>& isDriver, const std::vector<char>& onPath) {
    if (!cell.road) return " ";
    if (i == data.client) return BOLD + GREEN + "C" + RESET;
    if (isDriver[i]) return BOLD + YELLOW + "D" + RESET;
    if (onPath[i]) return BOLD + CYAN + "*" + RESET;
    return "o";
}

}

void render(CityMap& map, const RenderData& data) {
    int n = map.w * map.h;
    std::vector<char> isDriver(n, 0);
    std::vector<char> onPath(n, 0);
    std::set<std::pair<int, int>> pathLinks;

    for (int d : data.drivers) isDriver[d] = 1;
    for (int v : data.path) onPath[v] = 1;
    for (size_t i = 0; i + 1 < data.path.size(); ++i) {
        int a = data.path[i];
        int b = data.path[i + 1];
        pathLinks.insert({std::min(a, b), std::max(a, b)});
    }

    auto linkOnPath = [&](int u, int v) {
        return pathLinks.count({std::min(u, v), std::max(u, v)}) > 0;
    };

    for (int y = 0; y < map.h; ++y) {
        std::string row;
        for (int x = 0; x < map.w; ++x) {
            int i = y * map.w + x;
            row += nodeSymbol(map.at(x, y), i, data, isDriver, onPath);
            if (x + 1 < map.w) {
                Link l = linkBetween(map, x, y, RIGHT);
                row += horizontalLink(l, linkOnPath(i, i + 1));
            }
        }
        std::cout << row << '\n';

        if (y + 1 < map.h) {
            std::string between;
            for (int x = 0; x < map.w; ++x) {
                int i = y * map.w + x;
                Link l = linkBetween(map, x, y, DOWN);
                between += verticalLink(l, linkOnPath(i, i + map.w));
                if (x + 1 < map.w) between += "   ";
            }
            std::cout << between << '\n';
        }
    }

    std::cout << '\n'
              << GREEN << "wolno" << RESET << "  "
              << YELLOW << "gesto" << RESET << "  "
              << RED << "korek / X zamkniete" << RESET << "  "
              << MAGENTA << "R remont" << RESET << "  "
              << CYAN << "= trasa" << RESET << '\n'
              << "C klient   D kierowca   * wezel na trasie\n";
}