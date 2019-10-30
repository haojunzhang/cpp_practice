#include "FileUtils.h"

bool FileUtils::is_exist(std::string file_name)
{
    struct stat buf;
    if (stat(file_name.c_str(), &buf) != -1)
    {
        return true;
    }
    return false;
}

std::string FileUtils::read_file(std::string file_name)
{
    std::fstream file;
    file.open(file_name, std::ios::in);

    if (!file)
    {
        return std::strerror(errno);
    }

    std::string result = "";

    char buffer[1024];

    while (!file.eof())
    {
        file.getline(buffer, sizeof(buffer));

        // No next line at first
        if (result.length() == 0)
        {
            result += buffer;
        }
        else
        {
            result += "\n";
            result += buffer;
        }
    }

    file.close();

    return result;
}

bool FileUtils::write_file(std::string file_name, std::string text)
{
    std::fstream file;
    file.open(file_name, std::ios::out);

    if (!file)
    {
        std::cout << std::strerror(errno) << std::endl;
        return false;
    }
    file << text;
    file.close();
    return FileUtils::is_exist(file_name);
}

bool FileUtils::remove(std::string file_name)
{
    return std::remove(file_name.c_str()) == 0;
}