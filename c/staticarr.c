int sum(int arr[static 10]) {
  int s = 0;

  for(long i=0; i<10; ++i) {
    s += arr[i];
  }

  return s;
}

int main() {
  return sum((int[10]){1,2,3,4,5,6,8,9,10,11});
}

