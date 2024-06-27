#include "../Astar/grid.h"
#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(600, 600), "SFML Grid Example");
    Grid grid;
    bool done = false;

    // Create a button
    sf::RectangleShape button(sf::Vector2f(100, 50)); // Width: 100, Height: 50
    button.setPosition(500, 350); // Positioned at bottom-right corner of the window
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

                    // Check if the click is within the button boundaries
                    if (x >= button.getPosition().x && x <= button.getPosition().x + button.getSize().x &&
                        y >= button.getPosition().y && y <= button.getPosition().y + button.getSize().y) {
                        done = true; // Activate 'done' state when button is clicked
                    } else {
                        // Calculate the indices in the grid array
                        int i = x / (400 / 10); // Assuming window width is 400
                        int j = y / (400 / 10); // Assuming window height is 400

                        if (i >= 0 && i < 10 && j >= 0 && j < 10) {
                            grid.grid[i][j].toggleWall();
                        }
                    }
                }
            }
        }

        window.clear(); // Clear previous drawings

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
        

        // Update and draw grid if 'done' is true
        if (done) {
            grid.update(window);
            grid.draw(window);
        }

        window.display(); // Display all drawn objects
    }

    return 0;
}
