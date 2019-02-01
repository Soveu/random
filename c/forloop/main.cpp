#include<vector>
#include<array>
#include<iostream>

int main(){
	std::vector<int> v = {4, 5, 6, 7};
	std::array<int, 4> a{0, 1, 2, 3};

	for(auto& i : a){
		std::cout << i << '\n';
	}

	for(auto& i : v){
		std::cout << i << '\n';
	}

	std::cout << std::flush;
}

