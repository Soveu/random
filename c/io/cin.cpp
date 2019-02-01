#include<iostream>
#include<iomanip>
#include<unistd.h>

size_t const bufsize = 8;

int main(){
	std::ios::sync_with_stdio(false);
	char buf[bufsize+1];
	int b;

        buf[bufsize] = 0;
loop:
        size_t readbytes = read(0, buf, bufsize);
	std::cout << readbytes << '\n' << buf << '\n';
        if(readbytes == bufsize && buf[bufsize-1] != '\n') goto loop;

	return 0;
}

