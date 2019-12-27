#include <fstream>
#include <vector>
#include <array>

#include <stdint.h>

int const gridWidth     = 960;
int const gridHeight    = 540;

using Grid = std::vector<uint8_t>;

struct Point {
  int x, y;
};

const uint8_t colors[] = {0xFF, 0xDD, 0xBB, 0x99, 0x77, 0x55, 0x33, 0x11};

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

bool grow_step(Grid* g, std::vector<Point>* queue, uint8_t c, Pcg32* rng) {
  /* Non-production code random element picker */
  Point coords;
  do {
    if(queue->size() == 0) {
      return false;
    }
    size_t index = rng->random() % queue->size();
    coords = (*queue)[index];
    (*queue)[index] = queue->back();
    queue->pop_back();
  } while((*g)[coords.y * gridWidth + coords.x] != 0);

  (*g)[coords.y * gridWidth + coords.x] = c;
  if(coords.x > 0 && (*g)[coords.y * gridWidth + coords.x-1] == 0) {
    queue->push_back({coords.x-1, coords.y});
  }
  if(coords.y > 0 && (*g)[(coords.y-1) * gridWidth + coords.x] == 0) {
    queue->push_back({coords.x, coords.y-1});
  }
  if(coords.x < gridWidth-1 && (*g)[coords.y * gridWidth + coords.x+1] == 0) {
    queue->push_back({coords.x+1, coords.y});
  }
  if(coords.y < gridHeight-1 && (*g)[(coords.y+1) * gridWidth + coords.x] == 0) {
    queue->push_back({coords.x, coords.y+1});
  }

  return true;
}

int main() {
  Pcg32 rng;
  Grid grid(gridHeight * gridWidth);
  std::array<std::vector<Point>, 7> queues;

  for(auto& queue : queues) {
    queue.push_back({
      rng.random() % gridWidth, 
      rng.random() % gridHeight
    });
  }

  bool isWorking = true;
  do {
    bool flag = false;
    for(int i=0; i<queues.size(); ++i) {
      flag = grow_step(&grid, &(queues[i]), colors[i], &rng) || flag;
    }
    isWorking = flag;
  } while(isWorking);

  std::fstream f("map.data", std::ios::binary | std::ios::out | std::ios::trunc);
  f.write(reinterpret_cast<char*>(grid.data()), gridHeight*gridWidth*sizeof(grid[0]));

  return 0;
}

