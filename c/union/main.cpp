#include<iostream>
#include<array>

using byte = unsigned char;

union X{
    double d;
    void* v;
};

int main(){
    X x = {1.0 / 0.0};
    std::cout << x.v << '\n';
    x.d = -1.0 / 0.0;
    std::cout << x.v << '\n';
    x.d = 1.0;
    std::cout << x.v << '\n';
    x.d = 2.0;
    std::cout << x.v << '\n';
    x.d = 4.0;
    std::cout << x.v << '\n';

    return 0;
}
