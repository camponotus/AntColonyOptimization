#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

class Simulation
{
public:
    float alpha; // distance power
    float beta;  // pheromone power
    float rho;   // 1 - p. (p = evaporation rate)
    float q;     // pheromone intensity
    float sd;    // default pheromone intensity(strength default)
    int antNum;  // number of ants

    Simulation();
    void Action();

    void InsertPoint(sf::Vector2f pos);
    void Clear();
    void Render(sf::RenderTarget &target);

private:
    struct Edge
    {
        float length;
        float strength;
        sf::RectangleShape shape;
    };

    std::vector<Edge> _edges;
    std::vector<sf::CircleShape> _points;
};