#include<iostream>

using namespace std;

enum Sample{ ZERO, ONE, TWO }; 

int main(){
	Sample s = Sample::ONE;

	for(int i=0; i<20; ++i){
		switch(s){
		case Sample::ZERO:
			cout << "ZERO!";
			break;
		case Sample::ONE:
			cout << "ONE!";
			break;
		case Sample::TWO:
			cout << "TWO!";
			break;
		}

		s = static_cast<Sample>((s + 1) % 3);
		cout << endl;
	}

	return 0;
}

