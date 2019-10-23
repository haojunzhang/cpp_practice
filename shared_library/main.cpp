#include <iostream>
#include "sum.h"
using namespace std;
int main()
{
    double a = 2.6, b = 4.2, c = 0.0;
    c = sum(a, b);
    cout << c << endl;
    return 0;
}

// 1. clang++ -c -fPIC -o sum.o sum.cpp
// 2. clang++ -shared -o libsum.so sum.o
// 3. clang++ main.cpp libsum.so -o main
// 4. ./main