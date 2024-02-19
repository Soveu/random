#include <iostream>
#include <typeinfo>
#include <variant>

struct A { void f() const {} };
// struct B { void f() const {} };
struct B { };

using V = std::variant<A, B>;

int main() {
    const V v{};
    std::visit([](const auto& x) { x.f(); }, v);
    std::visit([](const auto& x) { std::cout << typeid(x).name() << std::endl; }, v);
}
