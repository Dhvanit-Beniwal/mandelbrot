#include <SFML/Graphics.hpp>
#include <deque>
#include <iostream>

int window_x = 1000;
int window_y = 800;

#include "mandelbrot.h"
#include "color_palette.h"
#include "render.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(window_x, window_y), "Mandelbrot");
    mandelRender m;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type){
                case sf::Event::Closed:
                    window.close();
                    break;
                
                case sf::Event::MouseButtonPressed:
                    if (event.mouseButton.button == sf::Mouse::Left){
                        m.move(event.mouseButton.x, event.mouseButton.y, 0.5); //move to place and zoom in
                    }
                    break;
                
                case sf::Event::KeyPressed:
                    if(event.key.code == sf::Keyboard::R){
                        m.reset(); //reset
                    }
                    if(event.key.code == sf::Keyboard::Z){
                        (event.key.shift ? m.zoom(2) : m.zoom(0.5)); //zoom in/out
                    }
                    break;
                
                default: break;
            }
        }

        m.enhance();

        window.clear();
        window.draw(m.render());
        window.display();
    }

    return 0;
}
