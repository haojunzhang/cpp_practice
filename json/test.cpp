#include <iostream>
#include <string>
#include "json.hpp"
using json = nlohmann::json;
using namespace std;

int main()
{
    json j;
    j["pi"] = 3.14;
    j["is_admin"] = true;
    j["name"] = "John";
    j["null"] = nullptr;

    j["obj"] = {{"obj_name", "Tom"}};
    j["arr"] = {1, 2, 3};

    for (int i = 0; i < 3; i++)
    {
        json j_obj;
        j_obj["x"] = 10;
        j_obj["y"] = 10;
        j["obj_arr"].push_back(j_obj);
    }

    cout << j.dump(4) << endl;

    cout << "---" << endl;
    json j_parse = json::parse(j.dump(4));
    cout << j_parse << endl;

    return 0;
}
// clang++ -std=c++11 test.cpp