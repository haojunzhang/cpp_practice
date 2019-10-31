#include "TimeUtils.h"

std::string time_format(time_t time, std::string format, bool use_utc)
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

std::string TimeUtils::now(bool use_utc)
{
    return time_format(time(nullptr), "%Y-%m-%d %H:%M:%S", use_utc);
}

std::string TimeUtils::unix_time_milliseconds()
{
    std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
    return std::to_string(ms.count());
}

std::string TimeUtils::unix_time_seconds()
{
    std::string s = unix_time_milliseconds();
    return s.substr(0, s.length() - 3);
}

time_t TimeUtils::str_to_time_t(std::string str)
{
    struct tm tm;
    strptime(str.c_str(), "%Y-%m-%d %H:%M:%S", &tm);
    time_t t = mktime(&tm);
    return t;
}

int TimeUtils::compare_time(std::string str_time1, std::string str_time2)
{
    time_t time1 = TimeUtils::str_to_time_t(str_time1);
    time_t time2 = TimeUtils::str_to_time_t(str_time2);
    return time1 > time2 ? 1 : (time1 == time2 ? 0 : -1);
}