#ifndef GRID_H
#define GRID_H

#include <vector>
#include <algorithm>  // For std::find
#include "spot.h"
#include <cmath>  

class Grid {
private:
    int rows = 10;  // number of rows in the grid
    int cols = 10;  // number of columns in the grid


public:
    sf::Clock clock;
    float updateInterval = 0.5f;  // seconds between updates
    Spot *needed = nullptr;

    Grid();  // Constructor
    void draw(sf::RenderWindow &window);
    void removeFromVector(std::vector<Spot*>& vec, Spot* current);
   

    std::vector<std::vector<Spot>> grid;
    bool done;
    std::vector<Spot*> openSet;
    std::vector<Spot*> closedSet;
    std::vector<Spot*> Path;
    void update(sf::RenderWindow &window);
    void reconstructPath(Spot *current);
    Spot* start;
    Spot* end;
    bool isRunning;
   

    std::vector<std::vector<Spot>>& getGrid();  // Accessor for the grid
    bool includes(const std::vector<Spot*>& vec, Spot* element);
    
    double dist(int x1, int y1, int x2, int y2);
    double heuristic(Spot *a, Spot* b);
};

#endif
