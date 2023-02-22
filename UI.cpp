#include "UI.hpp"

// class Button
Button::Button(sf::FloatRect rect, std::function<void()> onCLick)
    : _collider(rect),
      _onClick(onCLick),
      _shape(sf::Vector2f(rect.width, rect.height))
{
    _shape.setPosition(rect.left, rect.top);
}

bool Button::Contains(const sf::Vector2f &pos)
{
    return _collider.contains(pos);
}

void Button::Click()
{
    if (_onClick)
        _onClick();
}

void Button::Render(sf::RenderTarget &target)
{
    target.draw(_shape);
}

// class Slider
Slider::Slider(sf::FloatRect rect, std::function<void(float)> onSlide, float rate)
    : _rate(rate),
      _graped(false),
      _collider(rect),
      _onSlide(onSlide),
      _track(sf::Vector2f(rect.width, rect.height))
{
    _track.setPosition(rect.left, rect.top);

    static sf::String glsl =
        " uniform vec2 u_resolution;"
        " uniform vec2 u_position;"
        " uniform float u_rate;"

        " void main()"
        " {"
        "     vec2 st = (gl_FragCoord.xy-u_position) / u_resolution.xy;"
        "     vec3 color = vec3(1, 1, 1);"
        "     float tr = 0.4;"
        "     if (st.x < u_rate)"
        "     {"
        "          tr = 1.0;"
        "     };"
        "      gl_FragColor = vec4(color, tr);"
        " }";
    _shader.loadFromMemory(glsl, sf::Shader::Fragment);
    _shader.setUniform("u_resolution", _track.getSize());
    _shader.setUniform("u_position", _track.getPosition());
}

bool Slider::Contains(const sf::Vector2f &pos)
{
    return _collider.contains(pos);
}

void Slider::Click()
{
    _graped = true;
}

void Slider::Release()
{
    _graped = false;
}

void Slider::Slide(const sf::Vector2f &pos)
{
    if (!_graped)
        return;

    float dx = pos.x - _track.getPosition().x;
    float width = _track.getSize().x;
    float rate = dx / width;
    if (rate < 0)
        rate = 0;
    if (rate > 1)
        rate = 1;

    if (rate == _rate)
        return;

    _rate = rate;
    _shader.setUniform("u_rate", rate);

    _onSlide(rate);
}

void Slider::Render(sf::RenderTarget &target)
{
    target.draw(_track, &_shader);
}