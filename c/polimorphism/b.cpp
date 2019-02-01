#include<iostream>
#include<functional>

struct type_t {
  char*   name{0};
  size_t  hash{0};
}

using TypeRef = std::reference_wrapper<const std::type_info>;

std::ostream& operator<<(std::ostream& out, TypeRef type){
  out << type.get().name();
  return out;
}

struct Vtable{
  TypeRef type;
  void (*delete_)(void*);
  int (*foo_)(void*);
};

template <typename T>
Vtable const vtable_for = {
  std::ref(typeid(T)),
  [](void* this_){
    delete static_cast<T*>(this_);
  },
  [](void* this_){
    return static_cast<T*>(this_)->foo();
  }
};

struct Interface{
  const Vtable* vt{0};
  void* that{0};

  template <typename T>
  Interface(T* x) : that(static_cast<void*>(x)), vt(&vtable_for<T>) {};

  ~Interface(){
    vt->delete_(that);
    std::cout << "Deleted object with type " << vt->type << '\n';
  }

  constexpr int foo() const{
    return vt->foo_(that);
  }
};


struct Test{
  int a{123};
  ~Test(){
    std::cout << "Deleting Test with int: " << a << std::endl;
  }

  constexpr int foo() const noexcept{
    return a;
  }
};

struct ThatStructWithLongNameLol{
  char x;

  ~ThatStructWithLongNameLol(){
    std::cout << "Deleting letter " << x << '\n';
  }

  constexpr int foo() const noexcept{
    return static_cast<int>(x);
  }
};

void test(const Interface& i){
  std::cout << "\nHolding object type: " << i.vt->type 
    << "\nfoo() == " << i.foo() << '\n';

  return;
}

int main(){
  Interface i1(new Test{});
  Interface i2(new Test{777});
  Interface i3(new ThatStructWithLongNameLol{'c'});

  test(i1);
  test(i2);
  test(i3);

  std::cout << '\n';

  return 0;
}
