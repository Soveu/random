#include<iostream>

#include "fluid.hpp"
#include "ostream.hpp"

void test(Fluid f){
  std::cout << f["someFunc"](f) << '\n';
}

int main(){
  Fluid f1;
  Fluid f2{6.5};
  Fluid f3{std::string("Hello")};
  Fluid f4{Fluid::Array{
    Fluid{6.5},
    Fluid{},
    Fluid{"Hi"}
  }};

  Fluid f5{ Fluid::Object{
    { "foo", {6.5} },
    { "bar", {"baz"} }
  }};

  f4.push(f5);
  f4.push(true);

  Fluid::Function lamb = [](Fluid a) -> Fluid{
    return Fluid::Array{"There is my function! Recieved: ", a};
  };

  Fluid f6(lamb);
  f4.push(f6);
  f5["someFunc"] = f6;

  test(f5);

  std::cout 
    << f1 << '\n'
    << f2 << '\n'
    << f3 << '\n'
    << f4[3] << '\n'
    << f5 << '\n'
    << f5["foo"] << '\n'
    << f6 << '\n'
    << f4.pop()(f4) << '\n';

  return 0;
}

