#include <iostream>
#include "mapa.h"
#include <random>
#include "autko.h"
#include "render.h"
#ifdef _WIN32
#include <windows.h>
#include "client.h"
#include "Pathfinding.h"

#endif
using namespace std;
int main() {
    #ifdef _WIN32
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        DWORD dwMode = 0;
        GetConsoleMode(hOut, &dwMode);
        dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        SetConsoleMode(hOut, dwMode);
    #endif
    CityMap city = createUniformGrid (20, 20);

    
    const Cell& corner = city.at(0, 0);
    std::cout << "Komorka (0,0) - ruch w GORE zablokowany? " 
              << (corner.edge[UP].blocked ? "TAK" : "NIE") << "\n";
    std::cout << "Komorka (0,0) - ruch w PRAWO zablokowany? " 
              << (corner.edge[RIGHT].blocked ? "TAK" : "NIE") << "\n";

              
    Edge& testEdge = city.at(0, 0).edge[DOWN];
    testEdge.roadworks = 2.0f; 
    cout << "3. Sam remont (oczekiwane: 3): " 
         << travelCost(testEdge) << "\n";

       testEdge.cars = 9;
    cout << "4. Remont + korek (oczekiwane: 9): " 
         << travelCost(testEdge) << "\n";
    vector<Autko> auta;
    for (int i=0;i<7000;++i) {
        Autko a=city.rand_autko();
        auta.push_back(a);
    }
    render(city);

    std::mt19937 rng(std::random_device{}());   // do testów: stałe ziarno, np. rng(42)
    auto clients = generateClients(city, 3, rng);
    for (int i=0;i<clients.size();++i) {
        RenderData data;
        data.client = clients[i].spawn;
        auto res = Dijkstra::dijkstra(city, clients[i].spawn % city.w, clients[i].spawn / city.w);
        data.path = Dijkstra::buildPath(res, clients[i].dest);
        render(city, data);
    }


    return 0;

}