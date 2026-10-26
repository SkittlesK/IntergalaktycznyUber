class Punkt {
    public:
    double dist(Punkt p) {
        if (wymiary!=p.wymiary)
            throw std::runtime_error("Punkty mają różne wymiary");
    }
}
//
// Created by Eryk on 26.10.2026.
//