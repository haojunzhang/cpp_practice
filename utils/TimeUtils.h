#include <ctime>
#include <iostream>
#include <string>
#include <chrono>

class TimeUtils
{
public:
    static std::string now(bool);
    static std::string unix_time_milliseconds();
    static std::string unix_time_seconds();
    static time_t str_to_time_t(std::string);
    static int compare_time(std::string, std::string);
};