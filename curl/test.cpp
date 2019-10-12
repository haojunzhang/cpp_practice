#include <iostream>
#include <string>
#include "HttpClient.h"

void testPost()
{

    std::string url = "https://httpbin.org/post";
    std::vector<std::string> headers;

    HttpClient client;
    std::string response = client.http_post_with_json(url, headers, "");
    std::cout << response << std::endl;
}

int main(void)
{
    testPost();
    return 0;
}