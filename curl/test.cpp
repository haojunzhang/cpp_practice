#include <iostream>
#include <string>
#include "HttpClient.h"
#include "json.hpp"

void testGet()
{
    std::string url = "https://httpbin.org/get";

    // headers
    std::vector<std::string> headers;

    // add 'GET' params
    url += "?";
    url += "a=Hello";
    url += "&b=1";

    HttpClient client;
    std::string response = client.http_get(url, headers);
}

void testPost()
{

    std::string url = "https://httpbin.org/post";

    // headers
    std::vector<std::string> headers;
    headers.push_back("Content-Type: application/json");

    // post body
    nlohmann::json json_request;
    json_request["a"] = "Hello";
    json_request["b"] = 1;
    json_request["c"] = nullptr;

    HttpClient client;
    std::string response = client.http_post_with_json(url, headers, json_request.dump());
}

void testPut()
{

    std::string url = "https://httpbin.org/put";

    // headers
    std::vector<std::string> headers;
    headers.push_back("Content-Type: application/json");

    // post body
    nlohmann::json json_request;
    json_request["a"] = "Hello";
    json_request["b"] = 1;
    json_request["c"] = nullptr;

    HttpClient client;
    std::string response = client.http_put_with_json(url, headers, json_request.dump());
}

void testPatch()
{

    std::string url = "https://httpbin.org/patch";

    // headers
    std::vector<std::string> headers;
    headers.push_back("Content-Type: application/json");

    // post body
    nlohmann::json json_request;
    json_request["a"] = "Hello";
    json_request["b"] = 1;
    json_request["c"] = nullptr;

    HttpClient client;
    std::string response = client.http_patch_with_json(url, headers, json_request.dump());
}

void testDelete()
{
    std::string url = "https://httpbin.org/delete";

    // headers
    std::vector<std::string> headers;

    // add 'DELETE' params
    url += "?";
    url += "a=Hello";
    url += "&b=1";

    HttpClient client;
    std::string response = client.http_delete(url, headers);
}

int main(void)
{
    testGet();
    testPost();
    testPut();
    testPatch();
    testDelete();
    return 0;
} // clang++ -std=c++11 test.cpp HttpClient.cpp -lcurl