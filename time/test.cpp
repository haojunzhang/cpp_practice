#include <ctime>
#include <iostream>
#include <string>
#include <chrono>
using namespace std;
using namespace std::chrono;
string now()
{
    char buff[20];
    time_t now = time(nullptr);
    strftime(buff, 20, "%Y-%m-%d %H:%M:%S", localtime(&now));
    return buff;
}

string unix_time_milliseconds()
{
    milliseconds ms = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
    return to_string(ms.count());
}

string unix_time_seconds()
{
    string s = unix_time_milliseconds();
    return s.substr(0, s.length() - 3);
}

int main()
{
    cout << "now:" << now() << endl;
    cout << "unix time:" << unix_time_milliseconds() << " ms" << endl;
    cout << "unix time:" << unix_time_seconds() << " s" << endl;
} // clang++ test.cpp