#include<iostream>
#include<algorithm>

#define SWAP(a,b) decltype(a) __temp = (a); (a) = (b); (b) = __temp;
#define NOP __asm__("\n#############################################\n")

template<typename T>
void swap(T& a, T& b){
	T t = a;
	a = b;
	b = t;
}

template<typename T>
void dofunc(T f){
	f();
}

int main(){
	int a = 7;
	int b = 13;

	std::cin >> a >> b;

	NOP;

	SWAP(a,b);

	NOP;

	swap(a, b);

	NOP;

	std::swap(a, b);

	NOP;

	auto func = [&](){
		auto t = a;
		a = b;
		b = t;
	};

	dofunc(func);

	NOP;

	return 0;
}
