#pragma once
#include <functional>
#include <SFML/Graphics.hpp>

class Button
{
public:
    Button(sf::FloatRect rect, std::function<void()> onClick = nullptr);
    bool Contains(const sf::Vector2f &pos);
    void Click();
    void Render(sf::RenderTarget &target);

private:
    sf::FloatRect _collider;
    std::function<void()> _onClick;
    sf::RectangleShape _shape;
};

class Slider
{
public:
    Slider(sf::FloatRect rect, std::function<void(float)> onSlide = nullptr, float rate = 0.0f);
    bool Contains(const sf::Vector2f &pos);
    void Click();
    void Release();
    void Slide(const sf::Vector2f &pos);
    void Render(sf::RenderTarget &target);

private:
    float _rate;
    bool _graped;
    sf::FloatRect _collider;
    std::function<void(float)> _onSlide;
    sf::RectangleShape _track;
    sf::Shader _shader;
};