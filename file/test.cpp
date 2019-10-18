#include <iostream>
#include <string>
#include <fstream>
#include <sys/stat.h>
#include <stdio.h>
using namespace std;

bool is_exist(string file_name)
{
    struct stat buf;
    if (stat(file_name.c_str(), &buf) != -1)
    {
        return true;
    }
    return false;
}

string read_file(string file_name)
{
    fstream file;
    file.open(file_name, ios::in);

    if (!file)
    {
        cout << strerror(errno) << endl;
        exit(1);
    }

    string result = "";

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

bool write_file(string file_name, string text)
{
    fstream file;
    file.open(file_name, ios::out);

    if (!file)
    {
        cout << strerror(errno) << endl;
        exit(1);
        return false;
    }
    file << text;
    file.close();
    return is_exist(file_name);
}

int main()
{
    string read_file_name = "Readme.txt";
    string write_file_name1 = "Result1.txt";
    string write_file_name2 = "Result2.txt";
    string data = "data123";

    // Read file
    cout << "Exist:" << (is_exist(read_file_name) ? "Y" : "N") << endl;
    cout << read_file(read_file_name) << endl;

    // Write file
    cout << (write_file(write_file_name1, data) ? "Write success" : "Write fail") << endl;
    cout << (write_file(write_file_name2, data) ? "Write success" : "Write fail") << endl;

    // Delete file
    cout << (remove(write_file_name2.c_str()) == 0 ? "Delete success" : "Delete fail") << endl;
    cout << (remove(write_file_name2.c_str()) == 0 ? "Delete success" : "Delete fail") << endl;

    return 0;
} // clang++ test.cpp