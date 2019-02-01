#include<stdio.h>

typedef int (*myFuncDef)(int,int);
//typedef name = myFuncDef

int addInt(int n, int m) {
	return n+m;
}

int main() {
	//int (*functionPtr)(int, int);
	myFuncDef functionPtr;
	functionPtr = &addInt;

	int sum = (*functionPtr)(2,3);
	printf("%d\n", sum);
	return 0;
}

