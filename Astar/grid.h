#ifndef GRID_H
#define GRID_H

#include <vector>
#include <algorithm> 
#include "spot.h"
#include <cmath>  

class Grid {
private:
    int rows = 10;  
    int cols = 10;  


public:
    sf::Clock clock;
    float updateInterval = 0.5f;  
    Spot *needed = nullptr;

    Grid(); 
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
   

    std::vector<std::vector<Spot>>& getGrid();  
    bool includes(const std::vector<Spot*>& vec, Spot* element);
    
    double dist(int x1, int y1, int x2, int y2);
    double heuristic(Spot *a, Spot* b);
};

#endif
