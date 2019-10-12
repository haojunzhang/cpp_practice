#include <string>
#include "vector"

class HttpClient
{
private:
public:
    std::string http_get(std::string, std::vector<std::string>);
    std::string http_post_with_json(std::string, std::vector<std::string>, std::string);
    std::string http_put_with_json(std::string, std::vector<std::string>, std::string);
    std::string http_patch_with_json(std::string, std::vector<std::string>, std::string);
    std::string http_delete(std::string, std::vector<std::string>);
};