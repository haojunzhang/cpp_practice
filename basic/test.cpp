#include <iostream>
#include "Ball.h"
#include "vector"
#include "map"
#include <random>
#include "set"

void testVarOperate()
{
    cout << "==========" << endl;
    int a = 2;
    int b = 2;
    int sum = a + b;
    cout << "a + b = " << sum << endl;
}

void testIf()
{
    cout << "==========" << endl;
    int i = 13;
    if (i % 2 == 0)
    {
        cout << "sum is even" << endl;
    }
    else
    {
        cout << "sum is odd" << endl;
    }
}

void testFor()
{
    cout << "==========" << endl;
    int sum = 0;
    for (int i = 0; i < 10; i++)
    {
        sum += i;
    }
    cout << "sum = " << sum << endl;
}

void testClass()
{
    cout << "==========" << endl;
    Ball ball = Ball("BLUE", 5);
    ball.show_info();
}

void showVec(vector<int> &vec)
{
    string text;
    text += "[";
    for (int i = 0; i < vec.size(); i++)
    {
        if (i == 0)
        {
            text += to_string(vec[i]);
        }
        else
        {
            text += ", ";
            text += to_string(vec[i]);
        }
    }
    text += "]";
    cout << text << endl;
    // [1, 2, 3]
}

void testVectorAppend(vector<int> &vec)
{
    vec.push_back(4);
}

void testVector()
{
    cout << "==========" << endl;
    // append
    vector<int> vec;
    vec.push_back(10);
    vec.push_back(8);
    vec.push_back(6);
    testVectorAppend(vec);
    showVec(vec);

    // insert 5 to position 1
    vec.insert(vec.begin() + 1, 5);
    showVec(vec);

    // remove position 1 element
    vec.erase(vec.begin() + 1);
    showVec(vec);

    // sort
    sort(vec.begin(), vec.end());
    showVec(vec);
}

void testMap()
{
    cout << "==========" << endl;
    map<string, string> map_people;
    map<string, string>::iterator iter;

    map_people["A001"] = "Tom";
    map_people["A002"] = "John";
    map_people["A003"] = "Tommy";
    iter = map_people.find("A001");

    if (iter != map_people.end())
    {
        cout << iter->second << endl;
    }
    else
    {
        cout << "not found" << endl;
    }
}

int random_int(int from, int to)
{
    std::random_device rd;
    std::default_random_engine gen = std::default_random_engine(rd());
    std::uniform_int_distribution<int> dis(from, to);
    return dis(gen);
}

string random_text(int len)
{
    string text;
    char alphanum[] = "_-0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    // char alphanum[] = "0123456789";
    int alphanum_size = sizeof(alphanum) - 1;

    for (int i = 0; i < len; ++i)
    {
        text += alphanum[random_int(0, alphanum_size - 1)];
    }
    return text;
}

void testRandom()
{
    cout << "==========" << endl;
    srand((unsigned)time(NULL));
    for (int i = 0; i < 10; i++)
    {
        cout << random_text(20) << endl;
    }
}

void testSet()
{
    cout << "==========" << endl;
    set<string> set_text;
    for (int i = 0; i < 100; i++)
    {
        set_text.insert(random_text(2));
    }
    // check duplicate
    cout << set_text.size() << endl;
}

int main()
{
    cout << "Hello World!" << endl;
    testVarOperate();
    testIf();
    testFor();
    testClass();
    testVector();
    testMap();
    testRandom();
    testSet();
    return 0;
} // clang++ -std=c++11 test.cpp Ball.cpp