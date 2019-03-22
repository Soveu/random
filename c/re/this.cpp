struct S {
  int a;
  int b;
  char stuff[32];

  int get_a() {
    return a;
  }

  int get_b() {
    return b;
  }
};

S make_s() {
  S s{41,42};
  return s;
}

int main() {
  S s = make_s();

  return s.get_a() + s.get_b();
}

