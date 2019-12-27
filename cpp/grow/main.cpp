#include <iostream>
#include <vector>
#include <array>

#include "SFML/Graphics.hpp"

int const squareSize    = 3;
int const gridWidth     = 320;
int const gridHeight    = 180;
int const windowWidth   = squareSize * gridWidth;
int const windowHeight  = squareSize * gridHeight;

const sf::Color colors[] = {
  sf::Color::Red,
  sf::Color::Green,
  sf::Color::Blue,
  sf::Color::Magenta,
  sf::Color::Yellow,
  sf::Color::Cyan,
  sf::Color::White
};

using Grid = std::vector<std::array<sf::RectangleShape, gridWidth>>;

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

bool grow_step(Grid* g, std::vector<sf::Vector2i>* queue, sf::Color c, Pcg32* rng) {
  /* Non-production code random element picker */
  sf::Vector2i coords;
  do {
    if(queue->size() == 0) {
      return false;
    }
    size_t index = rng->random() % queue->size();
    coords = (*queue)[index];
    (*queue)[index] = queue->back();
    queue->pop_back();
  } while((*g)[coords.y][coords.x].getFillColor() != sf::Color::Black);

  (*g)[coords.y][coords.x].setFillColor(c);
  if(coords.x > 0 && (*g)[coords.y][coords.x-1].getFillColor() == sf::Color::Black) {
    queue->push_back({coords.x-1, coords.y});
  }
  if(coords.y > 0 && (*g)[coords.y-1][coords.x].getFillColor() == sf::Color::Black) {
    queue->push_back({coords.x, coords.y-1});
  }
  if(coords.x < gridWidth-1 && (*g)[coords.y][coords.x+1].getFillColor() == sf::Color::Black) {
    queue->push_back({coords.x+1, coords.y});
  }
  if(coords.y < gridHeight-1 && (*g)[coords.y+1][coords.x].getFillColor() == sf::Color::Black) {
    queue->push_back({coords.x, coords.y+1});
  }

  /*
  if(coords.x > 0 && coords.y > 0 && (*g)[coords.y-1][coords.x-1].getFillColor() == sf::Color::Black) {
    queue->push_back({coords.x-1, coords.y-1});
  }
  if(coords.x > 0 && coords.y < gridHeight-1 && (*g)[coords.y+1][coords.x-1].getFillColor() == sf::Color::Black) {
    queue->push_back({coords.x-1, coords.y+1});
  }
  if(coords.x < gridWidth-1 && coords.y > 0 && (*g)[coords.y-1][coords.x+1].getFillColor() == sf::Color::Black) {
    queue->push_back({coords.x+1, coords.y-1});
  }
  if(coords.x < gridWidth-1 && coords.y < gridHeight-1 && (*g)[coords.y+1][coords.x+1].getFillColor() == sf::Color::Black) {
    queue->push_back({coords.x+1, coords.y+1});
  }
  */

  return true;
}

int main() {
  sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Grow");
  window.setFramerateLimit(60);
  
  Pcg32 rng;
  Grid grid(gridHeight);
  std::array<std::vector<sf::Vector2i>, 7> queues;

  for(int i=0; i<gridHeight; ++i) {
    for(int j=0; j<gridWidth; ++j) {
      auto rect = sf::RectangleShape();
      rect.setSize(sf::Vector2f(squareSize, squareSize));
      rect.setFillColor(sf::Color::Black);
      //rect.setOutlineColor(sf::Color(0x3f, 0x3f, 0x3f));
      //rect.setOutlineThickness(1);
      rect.setPosition(j*squareSize, i*squareSize);
      grid[i][j] = rect;
    }
  }

  for(auto& queue : queues) {
    queue.push_back({rng.random() % gridWidth, rng.random() % gridHeight});
  }

  bool isWorking = true;
  while (window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
          window.close();
    }

    for(int i=0; isWorking && i<10; ++i) {
      bool flag = false;
      for(int i=0; i<queues.size(); ++i) {
        flag = grow_step(&grid, &(queues[i]), colors[i], &rng) || flag;
      }
      isWorking = flag;
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

