#include <iostream>
#include <string>
#include <curl/curl.h>
#include "vector"
#include "HttpClient.h"

static size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string *)userp)->append((char *)contents, size * nmemb);
    return size * nmemb;
}

std::string HttpClient::http_get(std::string url, std::vector<std::string> headers)
{
    return http_request(Method::GET, url, headers, "");
}

std::string HttpClient::http_post_with_json(std::string url, std::vector<std::string> headers,
                                            std::string json_data)
{
    return http_request(Method::POST, url, headers, json_data);
}

std::string HttpClient::http_put_with_json(std::string url, std::vector<std::string> headers,
                                           std::string json_data)
{
    return http_request(Method::PUT, url, headers, json_data);
}

std::string HttpClient::http_patch_with_json(std::string url, std::vector<std::string> headers,
                                             std::string json_data)
{
    return http_request(Method::PATCH, url, headers, json_data);
}

std::string HttpClient::http_delete(std::string url, std::vector<std::string> headers)
{
    return http_request(Method::DELETE, url, headers, "");
}

std::string HttpClient::http_request(Method method, std::string url,
                                     std::vector<std::string> headers, std::string json_data)
{
    std::cout << "[HttpClient]----------START----------" << std::endl;
    CURL *curl;
    CURLcode res;
    std::string read_buffer;

    curl = curl_easy_init();
    if (curl)
    {
        // url
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        std::cout << "[HttpClient]url:" << url << std::endl;

        // headers
        curl_slist *headers_params = NULL;
        for (std::string header : headers)
        {
            headers_params = curl_slist_append(headers_params, header.c_str());
        }
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers_params);

        if (method == Method::GET)
        {
            std::cout << "[HttpClient]method:GET" << std::endl;
        }
        else if (method == Method::POST)
        {
            std::cout << "[HttpClient]method:POST" << std::endl;
            // post data
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_data.c_str());
            curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
        }
        else if (method == Method::PUT)
        {
            std::cout << "[HttpClient]method:PUT" << std::endl;
            // post data
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_data.c_str());
            curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");
        }
        else if (method == Method::PATCH)
        {
            std::cout << "[HttpClient]method:PATCH" << std::endl;
            // post data
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_data.c_str());
            curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PATCH");
        }
        else if (method == Method::DELETE)
        {
            std::cout << "[HttpClient]method:DELETE" << std::endl;
            curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");
        }

        // response
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &read_buffer);

        // go
        res = curl_easy_perform(curl);

        // status code
        long http_status_code = 0;
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_status_code);
        std::cout << "[HttpClient]http_status_code:" << http_status_code << std::endl;

        if (res != CURLE_OK)
        {
            return curl_easy_strerror(res);
        }

        // clean
        curl_easy_cleanup(curl);

        std::cout << "[HttpClient]response:" << read_buffer << std::endl;
        std::cout << "[HttpClient]----------END----------" << std::endl;
        return read_buffer;
    }
    std::cout << "[HttpClient]----------END----------" << std::endl;
    return NULL;
}