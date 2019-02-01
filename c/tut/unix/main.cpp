#include<fstream>

int main(){
  std::ofstream cout;
  cout.open("/dev/stdout");
  cout << "Hello World!\n";
  cout.close();

  std::ifstream cin("/dev/stdin");
  // cin << "Not here!\n"; // Throws error on compilation

  int x;
  cin >> x;

  return x;
}

