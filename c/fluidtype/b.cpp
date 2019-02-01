#include<string>
#include<vector>
#include<functional>
#include<typeinfo>

struct Undefined{};

struct Fluid {
  using Type = std::reference_wrapper<const std::type_info>;
  Type type;

  union {
    Undefined               undef;
    double                  number;
    std::basic_string<char> str;
  } value;

  template<typename T>
  Fluid(const T& x) : type(typeid(T)), value{x} {};

  void dtorCurrent(){

  }

  ~Fluid(){
    _dtorCurrent();
  }
}

int main() {

  return 0;
}

