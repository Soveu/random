#include<stdio.h>

int main(){
	char a[2];
	int b=0;

	scanf("%2s%d%x%x%x", &a, &b);
	printf("a = '%s', b = %d\n", a, b);

	return 0;
}
