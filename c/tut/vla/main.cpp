#include<fstream>

int main(){
  std::ofstream cout("/dev/stdout");
  std::ifstream cin("/dev/stdin");
  size_t s;

  cout << sizeof(s) << '\n';
  cout.flush();

  cin >> s;

  char vla[s];
  cout << sizeof(vla) << '\n';
  cout.flush();

  vla[s-1] = 0;
  cout << (void*)&vla[s-1] << '\n';
  cout.flush();

  vla[0] = 0;
  cout << (void*)&vla[0] << '\n';
  cout.flush();

  return 0;
}

