void f(char const* const x[static 5]) {}

int main() {
  static const void(*x)(const char const* const [static const 5]);
}
