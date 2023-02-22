#include <cmath>
#include <random>
#include <utility>

#include "Simulation.hpp"

std::random_device rd_;
std::mt19937 gen_(rd_());

constexpr float PI = 3.14159265358979323846;
constexpr float RAD_TO_DEG = 180.0f / PI;

static inline float getLength2(sf::Vector2f v)
{
    return v.x * v.x + v.y * v.y;
}

static inline float getLength(sf::Vector2f v)
{
    return std::sqrtf(getLength2(v));
}

static inline float getAngle(sf::Vector2f v)
{
    return std::atan2f(v.y, v.x) * RAD_TO_DEG;
}

static inline int getEdgeIdx(int a, int b)
{
    if (a < b)
        std::swap(a, b);
    return a * (a - 1) / 2 + b;
}

// class Simulation
Simulation::Simulation()
    : alpha(0), beta(0), rho(0), q(0), sd(1),
      antNum(1)
{
}

void Simulation::Action()
{
    int pointNum = _points.size();
    if (pointNum < 2)
        return;

    std::vector<float> desirable(pointNum);
    std::vector<int> path(pointNum);
    std::vector<bool> visited(pointNum, false);

    // Select a random starting point
    std::uniform_int_distribution<int> start_dist(0, pointNum - 1);
    int start = start_dist(gen_);
    int cur = start;
    visited[cur] = true;

    // Select a path by desirable until all points are visited
    for (int i = 0; i < pointNum - 1; i++)
    {
        // Prove the deirable
        for (int j = 0; j < pointNum; j++)
        {
            if (visited[j] == true)
            {
                desirable[j] = 0;
            }
            else
            {
                int idx = getEdgeIdx(cur, j);
                float tau_pow = std::pow(_edges[idx].strength, alpha);
                float eta_pow = std::pow(1 / _edges[idx].length, beta);
                float weigth = tau_pow * eta_pow;
                desirable[j] = weigth ? weigth : 0.00001f;
            }
        }

        // Select a path
        std::discrete_distribution<int> next_dist(desirable.begin(), desirable.end());
        int next = next_dist(gen_);
        path[i] = getEdgeIdx(cur, next);
        cur = next;
        visited[cur] = true;
    }

    // Add the path from end to start
    path[pointNum - 1] = getEdgeIdx(cur, start);

    // Get delta_tau described by path
    float length = 0;
    for (int p : path)
        length += _edges[p].length;
    float delta_tau = q / length;

    // Update _edges
    for (auto &e : _edges)
        e.strength = e.strength * (1 - rho); //: evaporation
    for (int p : path)
    {
        float strength = _edges[p].strength + delta_tau;
        if (strength > 1)
            strength = 1;
        _edges[p].strength = strength; //: pheromone
    }
    // : view
    for (auto &e : _edges)
    {
        sf::Uint8 br = 255 * e.strength;
        e.shape.setFillColor(sf::Color(255, 255, 255, br));
    }
}

void Simulation::InsertPoint(sf::Vector2f pos)
{
    constexpr float Radius = 8;
    constexpr float EdgeThickness = 4;
    int pointNum = _points.size();

    std::vector<Edge> edges(pointNum);
    for (int i = 0; i < pointNum; i++)
    {
        sf::Vector2f v = _points[i].getPosition() - pos;
        float length = getLength(v);

        edges[i].length = length;
        edges[i].strength = sd;
        edges[i].shape.setSize(sf::Vector2f(length, EdgeThickness));
        edges[i].shape.setOrigin(0, EdgeThickness / 2.f);
        edges[i].shape.setPosition(pos);
        edges[i].shape.setRotation(getAngle(v));
    }
    _edges.insert(_edges.end(), edges.begin(), edges.end());

    sf::CircleShape point(Radius);
    point.setPosition(pos);
    point.setOrigin(Radius, Radius);
    _points.push_back(point);
}

void Simulation::Clear()
{
    _edges.clear();
    _points.clear();
}

void Simulation::Render(sf::RenderTarget &target)
{
    for (const auto &e : _edges)
        target.draw(e.shape);
    for (const auto &p : _points)
        target.draw(p);
}