#include <string>
#include <curl/curl.h>
#include "vector"
#include "HttpClient.h"

static size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string *)userp)->append((char *)contents, size * nmemb);
    return size * nmemb;
}

std::string HttpClient::http_post_with_json(std::string url, std::vector<std::string> headers,
                                            std::string json_data)
{
    CURL *curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if (curl)
    {
        // url
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        // headers
        curl_slist *headers_params = NULL;
        for (std::string header : headers)
        {
            headers_params = curl_slist_append(headers_params, header.c_str());
        }
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers_params);

        // post data
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_data.c_str());

        // response
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);

        if (res != CURLE_OK)
        {
            return curl_easy_strerror(res);
        }

        // clean
        curl_easy_cleanup(curl);

        return readBuffer;
    }
    return NULL;
}