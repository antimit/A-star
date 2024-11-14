#ifndef SPOT_H
#define SPOT_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <algorithm>  
#include <random>



class Spot {
private:
    

public:
    int i,j;
    double w1, h1;
    bool isWall;
    Spot * previous;
    sf::RectangleShape cell;
    double f, g, h;
    Spot() : f(0), g(0), h(0), w1(0), h1(0) {
      
        
    }
    Spot(int i, int j);
    void initVariables();
    sf::RectangleShape& getCell();
    std::vector< Spot *> neighbors;
    void toggleWall();
    void addNeighbors(std::vector<std::vector<Spot>>& grid, int rows, int cols);
 
};


#endif
