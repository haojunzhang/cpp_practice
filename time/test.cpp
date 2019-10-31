#include <iostream>
#include <string>
#include "../utils/TimeUtils.h"

int main()
{
    std::cout << "now:" << TimeUtils::now(false) << std::endl;
    std::cout << "now use utc:" << TimeUtils::now(true) << std::endl;
    std::cout << "unix time:" << TimeUtils::unix_time_milliseconds() << " ms" << std::endl;
    std::cout << "unix time:" << TimeUtils::unix_time_seconds() << " s" << std::endl;
    std::cout << "2019-10-10 10:10:10 to time_t:" << TimeUtils::str_to_time_t("2019-10-10 10:10:10") << std::endl;
    std::cout << "compare time1:" << TimeUtils::compare_time("2019-10-10 10:10:10", "2019-10-10 10:10:09") << std::endl;
    std::cout << "compare time2:" << TimeUtils::compare_time("2019-10-10 10:10:10", "2019-10-10 10:10:10") << std::endl;
    std::cout << "compare time3:" << TimeUtils::compare_time("2019-10-10 10:10:10", "2019-10-10 10:10:11") << std::endl;
} // clang++ test.cpp ../utils/TimeUtils.cpp