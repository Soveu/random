void foo1(const int* x) {
  *x = 42;
  x++;
  return;
}

/* The same as foo1 */
void foo2(int const* x) {
  *x = 42;
  x++;
  return;
}

/* Now the pointer is const */
void foo3(int* const x) {
  *x = 42;
  x++;
  return;
}

int main() {
  int a=0;

  void(*const ptr)(int* const) = foo3;
  ptr++;

  foo1(&a);
  foo2(&a);
  foo3(&a);

  return 0;
}

