#include<iostream>

int main(){
	std::basic_string<double> bs{0.5, 0.25, 0.125};

	for(auto& x : bs){
		std::cout << x << ' ';
	}

	std::cout << (bs[0] > bs[1]) <<  std::endl;
	auto t = bs[0];
	bs[0] = bs[1];
	bs[1] = t;

	for(auto& x : bs){
		std::cout << x << ' ';
	}
	return 0;
}
