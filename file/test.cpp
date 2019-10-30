#include <iostream>
#include <string>
#include <fstream>
#include <sys/stat.h>
#include <stdio.h>

#include "../utils/FileUtils.h"

using namespace std;

int main()
{
    string read_file_name = "Readme.txt";
    string write_file_name1 = "Result1.txt";
    string write_file_name2 = "Result2.txt";
    string data = "data123";

    // Read file
    cout << "Exist:" << (FileUtils::is_exist(read_file_name) ? "Y" : "N") << endl;
    string read_str = FileUtils::read_file(read_file_name);
    cout << read_str << endl;

    // Write file
    cout << (FileUtils::write_file(write_file_name1, data) ? "Write success" : "Write fail") << endl;
    cout << (FileUtils::write_file(write_file_name2, data) ? "Write success" : "Write fail") << endl;

    // Delete file
    cout << (FileUtils::remove(write_file_name2) ? "Delete success" : "Delete fail") << endl;
    cout << (FileUtils::remove(write_file_name2) ? "Delete success" : "Delete fail") << endl;

    return 0;
} // clang++ test.cpp ../utils/FileUtils.cpp