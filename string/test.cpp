#include <iostream>
#include <algorithm>
#include <string>
#include "../utils/StringUtils.h"
using namespace std;

int main()
{

    // reverse
    string s1 = "12345";
    reverse(s1.begin(), s1.end());
    cout << "reverse:" << s1 << endl;

    // substring
    string s2 = "12345";
    cout << "substr(1):" << s2.substr(1) << endl;
    cout << "substr(1, 3):" << s2.substr(1, 3) << endl;

    // insert
    string s3 = "12345";
    cout << "insert(1, \"0\")" << s3.insert(1, "0") << endl;

    // replace
    string s4 = "123,123,123,123";
    string replace_from = ",";
    string replace_to = ".";
    cout << "replace(\",\", \".\"):" << StringUtils::replace_all(s4, replace_from, replace_to) << endl;

    // Upper & Lower
    string str1 = "Hello World";
    string str2 = "Hello World";
    transform(str1.begin(), str1.end(), str1.begin(), ::toupper);
    transform(str2.begin(), str2.end(), str2.begin(), ::tolower);
    cout << "Upper:" << str1 << endl;
    cout << "Lower:" << str2 << endl;

    return 0;
} // clang++ test.cpp StringUtils.cpp