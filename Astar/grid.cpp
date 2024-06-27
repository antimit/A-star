#include "grid.h"

Grid::Grid()
    : rows(10), cols(10), grid(rows, std::vector<Spot>(cols)), isRunning(true),
      done(false) {
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      grid[i][j] = Spot(i, j);
      grid[i][j].initVariables(); // Ensure all variables are initialized
      
    }
  }

  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      grid[i][j].addNeighbors(grid, rows, cols);
    }
  }

  start = &grid[0][0];
  end = &grid[cols - 1][rows - 1];
  // start->wall = false;
  // end->wall = false;

  openSet.push_back(start);
}

void Grid::removeFromVector(std::vector<Spot *> &vec, Spot *current) {
  auto it = std::find(vec.begin(), vec.end(), current);
  if (it != vec.end()) {
    vec.erase(it);
  } else {
    // Handle the case where the element is not found if necessary
  }
}

bool Grid::includes(const std::vector<Spot *> &vec, Spot *element) {
  return std::find(vec.begin(), vec.end(), element) != vec.end();
}

double Grid::dist(int x1, int y1, int x2, int y2) {
  return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

double Grid::heuristic(Spot *a, Spot *b) {
  double d = dist(a->i, a->j, b->i, b->j);
  return d;
}

void Grid::draw(sf::RenderWindow &window) {
  if (!isRunning) {
    window.clear();
    std::cout << "works" << std::endl;

    for (size_t i = 0; i < 10; i++) {
      for (size_t j = 0; j < 10; j++) {
        sf::RectangleShape cell;
        cell = grid[i][j].getCell();
        window.draw(cell);
      }
    }

    for (size_t i = 0; i < openSet.size(); i++) {
      sf::RectangleShape cell;
      cell = openSet[i]->getCell();
      cell.setFillColor(sf::Color::Blue);
      window.draw(cell);
    }

    for (size_t i = 0; i < closedSet.size(); i++) {
      sf::RectangleShape cell;
      cell = closedSet[i]->getCell();
      cell.setFillColor(sf::Color::Red);
      window.draw(cell);
    }

    for (auto &spot : Path) {
      sf::RectangleShape cell = spot->getCell();
      cell.setFillColor(sf::Color::Yellow);
      window.draw(cell);
    }

    window.display();
    return;
  }

  // Stop drawing if isRunning is false

  window.clear();
  // Draw your grid and other elements

  for (size_t i = 0; i < 10; i++) {
    for (size_t j = 0; j < 10; j++) {
      sf::RectangleShape cell;
      cell = grid[i][j].getCell();
      window.draw(cell);
    }
  }

  for (size_t i = 0; i < openSet.size(); i++) {
    sf::RectangleShape cell;
    cell = openSet[i]->getCell();
    cell.setFillColor(sf::Color::Blue);
    window.draw(cell);
  }

  for (size_t i = 0; i < closedSet.size(); i++) {
    sf::RectangleShape cell;
    cell = closedSet[i]->getCell();
    cell.setFillColor(sf::Color::Red);
    window.draw(cell);
  }
  // Draw the path if done
  if (Path.size()) {
  }

  window.display();
}

void Grid::update(sf::RenderWindow &window) {
  if (!isRunning || clock.getElapsedTime().asSeconds() < updateInterval)
    return;
  clock.restart();

  if (openSet.empty())
    return;

  size_t winner = 0;
  for (size_t i = 0; i < openSet.size(); i++) {
    if (openSet[i]->f < openSet[winner]->f) {
      winner = i;
    }
  }

  Spot *current = openSet[winner];
  if (current == end) {
    std::cout << "DONE!" << std::endl;
    reconstructPath(current);
    done = true;
    isRunning = false;
    return;
  }

  removeFromVector(openSet, current);
  closedSet.push_back(current);

  auto neighbors = current->neighbors;
  for (size_t i = 0; i < neighbors.size(); i++) {
    auto neighbor = neighbors[i];
    if (!includes(closedSet, neighbor) && !neighbor->isWall) {
      auto tempG = current->g + heuristic(neighbor, current);

      auto newPath = false;

      if (!includes(openSet, neighbor)) {
        if (tempG < neighbor->g) {
          neighbor->g = tempG;
          newPath = true;
        } else {
          neighbor->h = tempG;
          newPath = true;
          openSet.push_back(neighbor);
        }

        if (newPath) {
          neighbor->h = heuristic(neighbor, end);
          neighbor->f = neighbor->g + neighbor->h;
          neighbor->previous = current;
        }
      }
    }
  }
}

void Grid::reconstructPath(Spot *current) {
  auto temp = current;
  Path.push_back(temp);
  while (temp->previous) {
    std::cout << "hello" << std::endl;
    Path.push_back(temp->previous);
    temp = temp->previous;
  }
}
