#include <ctime>
#include <iostream>
#include <string>
#include <chrono>
using namespace std;
using namespace std::chrono;

string time_format(time_t time, string format, bool use_utc)
{
    char buff[20];
    if (use_utc)
    {
        strftime(buff, 20, format.c_str(), gmtime(&time));
    }
    else
    {
        strftime(buff, 20, format.c_str(), localtime(&time));
    }

    return buff;
}

string now(bool use_utc)
{
    return time_format(time(nullptr), "%Y-%m-%d %H:%M:%S", use_utc);
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

time_t str_to_time_t(string str)
{
    struct tm tm;
    strptime(str.c_str(), "%Y-%m-%d %H:%M:%S", &tm);
    time_t t = mktime(&tm);
    return t;
}

string compare_time(string str_time1, string str_time2)
{
    time_t time1 = str_to_time_t(str_time1);
    time_t time2 = str_to_time_t(str_time2);
    return time1 > time2 ? "after" : (time1 == time2 ? "same" : "before");
}

int main()
{
    cout << "now:" << now(false) << endl;
    cout << "now use utc:" << now(true) << endl;
    cout << "unix time:" << unix_time_milliseconds() << " ms" << endl;
    cout << "unix time:" << unix_time_seconds() << " s" << endl;
    cout << "2019-10-10 10:10:10 to time_t:" << str_to_time_t("2019-10-10 10:10:10") << endl;
    cout << "compare time1:" << compare_time("2019-10-10 10:10:10", "2019-10-10 10:10:09") << endl;
    cout << "compare time2:" << compare_time("2019-10-10 10:10:10", "2019-10-10 10:10:10") << endl;
    cout << "compare time3:" << compare_time("2019-10-10 10:10:10", "2019-10-10 10:10:11") << endl;
} // clang++ test.cpp