int main() {
  int a = 0;
  int b = 1;

  switch(a) {
    case 0 ... 9:
      b = 2;
      break;
  }

  int c[12] = {[0 ... 11] = 42};

  return a ?: b;
}
