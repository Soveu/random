#include <iostream>
#include <unistd.h>
#include "stopwatch.cpp"

Stopwatch some_function(Stopwatch sw) {
  std::cout << sw.milliseconds() << '\n';
  sw.stop();
  sleep(1);
  std::cout << sw.milliseconds() << '\n';
  sw.resume();
  sleep(1);
  std::cout << sw.milliseconds() << '\n';

  return sw;
}

int main() {
  Stopwatch sw;

  std::cout << sw.milliseconds() << '\n'; // ~0 seconds

  sw.start();
  sleep(1);
  std::cout << sw.seconds() << '\n'; // 1 second

  sleep(1);
  sw.stop();
  std::cout << sw.milliseconds() << '\n'; // 2 seconds

  sleep(1);

  sw.resume();
  sleep(1);
  std::cout << sw.milliseconds() << '\n'; // 3 seconds

  sw = some_function(sw);

  sleep(1);
  std::cout << sw.milliseconds() << '\n';

  return 0;
}

