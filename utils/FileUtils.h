#include <fstream>
#include <sys/stat.h>
#include <stdio.h>

#include <iostream>
#include <string>

class FileUtils
{
public:
    static bool is_exist(std::string);
    static std::string read_file(std::string);
    static bool write_file(std::string, std::string);
    static bool remove(std::string);
};