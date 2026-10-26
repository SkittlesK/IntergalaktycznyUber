#pragma once
#include <vector>
#include <random>
#include "mapa.h"

struct Client {
    int id = -1;
    int spawn = -1;   // indeks węzła: y * w + x
    int dest = -1;    // indeks węzła celu
};

std::vector<Client> generateClients(CityMap& map, int count, std::mt19937& rng);