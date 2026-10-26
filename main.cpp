#include <iostream>
#include "mapa.h"
#include "render.h"
#ifdef _WIN32
#include <windows.h>
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
    CityMap city = createUniformGrid (5, 5);

    
    const Cell& corner = city.at(0, 0);
    std::cout << "Komorka (0,0) - ruch w GORE zablokowany? " 
              << (corner.edge[UP].blocked ? "TAK" : "NIE") << "\n";
    std::cout << "Komorka (0,0) - ruch w PRAWO zablokowany? " 
              << (corner.edge[RIGHT].blocked ? "TAK" : "NIE") << "\n";

              
    Edge& testEdge = city.at(1, 1).edge[DOWN];
    testEdge.roadworks = 2.0f; 
    cout << "3. Sam remont (oczekiwane: 3): " 
         << travelCost(testEdge) << "\n";

       testEdge.cars = 9;
    cout << "4. Remont + korek (oczekiwane: 9): " 
         << travelCost(testEdge) << "\n";

    render(city);
    return 0;

}