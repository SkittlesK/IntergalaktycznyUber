#include <iostream>
#include "mapa.h"
#include "render.h"

using namespace std;
int main() {
    CityMap city = createUniformGrid (5, 5);

    
    const Cell& corner = city.at(0, 0);
    std::cout << "Komorka (0,0) - ruch w GORE zablokowany? " 
              << (corner.edge[UP].blocked ? "TAK" : "NIE") << "\n";
    std::cout << "Komorka (0,0) - ruch w PRAWO zablokowany? " 
              << (corner.edge[RIGHT].blocked ? "TAK" : "NIE") << "\n";

    return 0;

}