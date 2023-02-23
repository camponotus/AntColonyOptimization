#include <iostream>
#include <SFML/Graphics.hpp>

#include "UI.hpp"
#include "Simulation.hpp"

constexpr unsigned int WINDOW_WIDTH = 1600;
constexpr unsigned int WINDOW_HEIGHT = 900;
constexpr unsigned int ANTIALIAS_LEVEL = 8;
constexpr unsigned int FRAME_LIMIT = 100;

int main()
{
    std::cout << "Ant colony optimization - main.cpp" << std::endl;

    sf::ContextSettings settings;
    settings.antialiasingLevel = ANTIALIAS_LEVEL;
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
                            "ACO - window",
                            sf::Style::Close | sf::Style::Titlebar,
                            settings);
    window.setFramerateLimit(FRAME_LIMIT);

    // Initialize
    Simulation simulation;
    bool running = false;
    sf::Clock clock;
    sf::Time lag;
    sf::Time interval;

    // - Set UI
    sf::RectangleShape pannel(sf::Vector2f(370, 180));
    pannel.setFillColor(sf::Color(96, 96, 96, 160));
    sf::Rect rect_pannel = pannel.getGlobalBounds();
    Button button_start(sf::FloatRect(10, 10, 100, 30), [&running, &simulation]
                        { std::cout << "restart" << std::endl;
                          simulation.Reset();
                          running = true; });
    Button button_pause(sf::FloatRect(130, 10, 100, 30), [&running, &simulation]
                        { std::cout << "stop" << std::endl;
                          simulation.Set(0);
                          running = false; });
    Button button_clear(sf::FloatRect(250, 10, 100, 30), [&simulation]
                        { std::cout << "clear" << std::endl;
                          simulation.Clear(); });
    Slider slider_alpha(sf::FloatRect(10, 50, 340, 10), [&simulation](float rate)
                        { float alpha = rate * 5;
                          simulation.alpha = alpha;
                          std::cout << "alpha = " << alpha << std::endl; });
    Slider slider_beta(sf::FloatRect(10, 70, 340, 10), [&simulation](float rate)
                       { float beta = rate * 5;
                         simulation.beta = beta;
                         std::cout << "beta = " << beta << std::endl; });
    Slider slider_rho(sf::FloatRect(10, 90, 340, 10), [&simulation](float rate)
                      { float rho = rate;
                        simulation.rho = rho;
                        std::cout << "rho = " << rho << std::endl; });
    Slider slider_q(sf::FloatRect(10, 110, 340, 10), [&simulation](float rate)
                    { float q = rate * 100;
                      simulation.q = q;
                      std::cout << "q = " << q << std::endl; });
    Slider slider_k(sf::FloatRect(10, 140, 340, 10), [&simulation](float rate)
                    { float k = rate * 100 + 1;
                      simulation.antNum = k;
                      std::cout << "k = " << k << std::endl; });
    Slider slider_interval(sf::FloatRect(10, 160, 340, 10), [&interval](float rate)
                           { interval = sf::seconds(rate/4);
                             std::cout << "interval = " << interval.asSeconds() << std::endl; });

    while (window.isOpen())
    {
        sf::Event e;
        while (window.pollEvent(e))
        {
            switch (e.type)
            {
            case sf::Event::MouseButtonPressed:
            {
                sf::Vector2f pos(e.mouseButton.x, e.mouseButton.y);
                switch (e.mouseButton.button)
                {
                case sf::Mouse::Button::Left:
                {
                    if (rect_pannel.contains(pos))
                    {
                        if (button_start.Contains(pos))
                            button_start.Click();
                        if (button_pause.Contains(pos))
                            button_pause.Click();
                        if (button_clear.Contains(pos))
                            button_clear.Click();
                        if (slider_alpha.Contains(pos))
                        {
                            slider_alpha.Click();
                            slider_alpha.Slide(pos);
                        }
                        if (slider_beta.Contains(pos))
                        {
                            slider_beta.Click();
                            slider_beta.Slide(pos);
                        }
                        if (slider_rho.Contains(pos))
                        {
                            slider_rho.Click();
                            slider_rho.Slide(pos);
                        }
                        if (slider_q.Contains(pos))
                        {
                            slider_q.Click();
                            slider_q.Slide(pos);
                        }
                        if (slider_k.Contains(pos))
                        {
                            slider_k.Click();
                            slider_k.Slide(pos);
                        }
                        if (slider_interval.Contains(pos))
                        {
                            slider_interval.Click();
                            slider_interval.Slide(pos);
                        }
                    }
                    else
                    {
                        simulation.InsertPoint(pos);
                    }
                    break;
                }
                }
                break;
            }
            case sf::Event::MouseButtonReleased:
            {
                switch (e.mouseButton.button)
                {
                case sf::Mouse::Button::Left:
                    slider_alpha.Release();
                    slider_beta.Release();
                    slider_rho.Release();
                    slider_q.Release();
                    slider_k.Release();
                    slider_interval.Release();
                    break;
                }
                break;
            }
            case sf::Event::MouseMoved:
            {
                sf::Vector2f pos(e.mouseMove.x, e.mouseMove.y);
                slider_alpha.Slide(pos);
                slider_beta.Slide(pos);
                slider_rho.Slide(pos);
                slider_q.Slide(pos);
                slider_k.Slide(pos);
                slider_interval.Slide(pos);
                break;
            }
            case sf::Event::Closed:
                window.close();
                break;

            default:
                break;
            }
        }

        // Update
        lag += clock.restart();
        while (lag > interval)
        {
            lag = sf::Time::Zero;
            if (running)
                simulation.Action();
        }

        // Render
        window.clear();

        simulation.Render(window);
        window.draw(pannel);
        button_start.Render(window);
        button_pause.Render(window);
        button_clear.Render(window);
        slider_alpha.Render(window);
        slider_beta.Render(window);
        slider_rho.Render(window);
        slider_q.Render(window);
        slider_k.Render(window);
        slider_interval.Render(window);

        window.display();
    }

    return EXIT_SUCCESS;
}