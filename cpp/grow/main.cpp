#include <vector>
#include <array>

#include "SFML/Graphics.hpp"

int const squareSize    = 10;
int const gridWidth     = 90;
int const gridHeight    = 70;
int const windowWidth   = squareSize * gridWidth;
int const windowHeight  = squareSize * gridHeight;

struct Pcg32 { 
  uint64_t state;
  uint64_t inc; 

  uint32_t random() {
    uint64_t oldstate = this->state;
    // Advance internal state
    this->state = oldstate * 6364136223846793005ULL + (this->inc|1);
    // Calculate output function (XSH RR), uses old state for max ILP
    uint32_t xorshifted = ((oldstate >> 18u) ^ oldstate) >> 27u;
    uint32_t rot = oldstate >> 59u;
    return (xorshifted >> rot) | (xorshifted << ((-rot) & 31));
  }
};

int main() {
  sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Grow");
  window.setFramerateLimit(60);
  
  Pcg32 rng;
  std::array<std::array<sf::RectangleShape, gridWidth>, gridHeight> grid;
  std::vector<sf::Vector2i> queued;

  for(int i=0; i<gridHeight; ++i) {
    for(int j=0; j<gridWidth; ++j) {
      auto rect = sf::RectangleShape();
      rect.setSize(sf::Vector2f(squareSize, squareSize));
      rect.setFillColor(sf::Color::Green);
      //rect.setOutlineColor(sf::Color::Red);
      //rect.setOutlineThickness(1);
      rect.setPosition(j*squareSize, i*squareSize);
      grid[i][j] = rect;
    }
  }

  queued.push_back({gridWidth/2, gridHeight/2});

  while (window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
          window.close();
    }

    /* Non-production code random element picker */
    size_t index = rng.random() % queued.size();
    const auto coords = queued[index];
    queued[index] = queued.back();
    queued.pop_back();

    if(grid[coords.y][coords.x].getFillColor() == sf::Color::Green) {
      grid[coords.y][coords.x].setFillColor(sf::Color::Red);
      if(coords.x > 0 && grid[coords.y][coords.x-1].getFillColor() != sf::Color::Red) {
        queued.push_back({coords.x-1, coords.y});
      }
      if(coords.x > 0 && grid[coords.y-1][coords.x].getFillColor() != sf::Color::Red) {
        queued.push_back({coords.x, coords.y-1});
      }
      if(coords.x < gridWidth-1 && grid[coords.y][coords.x+1].getFillColor() != sf::Color::Red) {
        queued.push_back({coords.x+1, coords.y});
      }
      if(coords.y < gridHeight-1 && grid[coords.y+1][coords.x].getFillColor() != sf::Color::Red) {
        queued.push_back({coords.x, coords.y+1});
      }
      /* TODO */
    }

    window.clear();
    for(const auto& row : grid) {
      for(const auto& rect : row) {
        window.draw(rect);
      }
    }
    window.display();
  }

  return 0;
}

