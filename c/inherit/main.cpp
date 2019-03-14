#include <vector>

class Buffer : public std::vector<char> {
public:
  size_t written = 0;

  using std::vector<char>::vector;
};

int main() {
  Buffer buf(16);

  return buf.size();
}

