#include <iostream>
#include <sstream>
#include <locale>
#include <iomanip>

#include <stdint.h>
#include <time.h>

const char* TIMEFORMAT = "%Y-%m-%d %T";

int main() {
  std::tm t1 = {};
  std::istringstream ss1("2011-02-18 23:12:34");
  ss1 >> std::get_time(&t1, TIMEFORMAT);
  
  std::tm t2 = {};
  std::stringstream ss2("2011-03-19 23:12:34");
  std::cin >> std::get_time(&t2, TIMEFORMAT);

  if (ss1.fail() || ss2.fail()) {
    std::cout << "Parse failed\n";
    return 1;
  }

  int64_t diff = mktime(&t1) - mktime(&t2);
  if(diff > 0) {
    std::cout << std::put_time(&t1, "%D %T") << '\n';
  } else {
    std::cout << std::put_time(&t2, "%D %T") << '\n';
  }

  std::string s;
  std::getline(std::cin, s);
  std::stringstream ss(std::move(s));
  ss >> s;
  std::cout << s;
  ss >> s;
  std::cout << s;
}

