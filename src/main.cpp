#include "../Astar/grid.h"
#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(600, 600), "SFML Grid Example");
    Grid grid;
    bool done = false;

    
    sf::RectangleShape button(sf::Vector2f(100, 50)); 
    button.setPosition(500, 350); 
    button.setFillColor(sf::Color::Red);
    button.setOutlineColor(sf::Color::White);
    button.setOutlineThickness(2);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left && done == false) {
                    int x = event.mouseButton.x;
                    int y = event.mouseButton.y;

                    
                    if (x >= button.getPosition().x && x <= button.getPosition().x + button.getSize().x &&
                        y >= button.getPosition().y && y <= button.getPosition().y + button.getSize().y) {
                        done = true; 
                    } else {
                       
                        int i = x / (400 / 10); 
                        int j = y / (400 / 10); 
                        if (i >= 0 && i < 10 && j >= 0 && j < 10) {
                            grid.grid[i][j].toggleWall();
                        }
                    }
                }
            }
        }

        window.clear(); 

        // Draw grid
        for (size_t i = 0; i < 10; i++) {
            for (size_t j = 0; j < 10; j++) {
                sf::RectangleShape cell = grid.grid[i][j].getCell();
                window.draw(cell);
            }
        }

        // Draw the button
        if(!done)
        {
            window.draw(button);
        }
        

        
        if (done) {
            grid.update(window);
            grid.draw(window);
        }

        window.display(); // Display all drawn objects
    }

    return 0;
}
