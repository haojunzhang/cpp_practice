#include <iostream>
#include "sum.h"
using namespace std;
int main()
{
    int result = 0;
    for (int i = 1; i <= 10; i++)
    {
        result = sum(result, i);
    }
    cout << result << endl;

    return 0;
}
// 0. libsum.so should exist
// 1. clang++ main2.cpp libsum.so -o main
