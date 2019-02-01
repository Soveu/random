#include<iostream>

template<typename T>
constexpr inline void swap(T& a, T& b) {
    T temp;
    temp = a;
    a = b;
    b = temp;
}
int main(){
    int a,b;
    std::cin >> a >> b;

    swap(a,b);

    return 0;
}
