#include<cmath>
#include<cassert>

int main() {
  float f1 = std::nan("");
  float f2 = std::nan("");

  assert(f1 == f2);
}
