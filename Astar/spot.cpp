#include "spot.h"

Spot::Spot(int i, int j) : i(i), j(j) {
    initVariables();  // Initialize defaults and setup cell

    static std::random_device rd;  // Seed with a real random value, if available
    static std::mt19937 rng(rd()); // Static to be initialized only once
    std::uniform_real_distribution<float> dist(0.0, 1.0);

    // Set wall based on random chance
    if (dist(rng) < 0.4) {
        isWall = true;
        cell.setFillColor(sf::Color::Black);
        std::cout << "Wall at " << i << ", " << j << std::endl;
    }
}

void Spot::initVariables() {
    isWall = false;  // Default to not being a wall
    w1 = 400 / 10;   // Assuming grid width and number of columns
    h1 = 400 / 10;   // Assuming grid height and number of rows
    cell.setSize(sf::Vector2f(w1, h1));
    cell.setPosition(i * w1, j * h1);
    cell.setFillColor(sf::Color::Green);  // Default color
    this->previous = nullptr;
    f = 0;
    g = 0;
    h = 0;
}

void Spot::toggleWall() {
    isWall = !isWall;
    cell.setFillColor(isWall ? sf::Color::Black : sf::Color::Green);
}


sf::RectangleShape& Spot::getCell() {
    return cell;
}

bool includes(const std::vector<Spot*>& vec, Spot* element) {
    return std::find(vec.begin(), vec.end(), element) != vec.end();
}

void Spot::addNeighbors(std::vector<std::vector<Spot>>& grid, int rows, int cols) {
        // Check right
        if ( i < cols - 1) {
            std::cout <<"yes" <<std::endl;
            neighbors.push_back(&grid[i + 1][j]);
        }
        // Check left
        if (i > 0) {
            neighbors.push_back(&grid[i - 1][j]);
        }
        // Check down
        if (j < rows - 1) {
            neighbors.push_back(&grid[i][j + 1]);
        }
        // Check up
        if (j > 0) {
            neighbors.push_back(&grid[i][j - 1]);
        }
        // Check diagonal top-left
        if (i > 0 && j > 0) {
            neighbors.push_back(&grid[i - 1][j - 1]);
        }
        // Check diagonal top-right
        if (i < cols - 1 && j > 0) {
            neighbors.push_back(&grid[i + 1][j - 1]);
        }
        // Check diagonal bottom-left
        if (i > 0 && j < rows - 1) {
            neighbors.push_back(&grid[i - 1][j + 1]);
        }
        // Check diagonal bottom-right
        if (i < cols - 1 && j < rows - 1) {
            neighbors.push_back(&grid[i + 1][j + 1]);
        }
}
