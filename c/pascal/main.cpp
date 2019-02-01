#include<iostream>

using namespace std;

int main(){
    int n;
    unsigned long int x = 1;
    cout << "Enter a row number for Pascal's Triangle: ";
    cin >> n; 

    int a = n;
    int b = 1;
    while(b < n){
        x = x * a / b;
        cout << x << '\t';

        --a;
        ++b;
    }
    cout << endl;
    return 0;
}
