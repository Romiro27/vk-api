/**
 * @author      : romiro27 (vanno6521@gmail.com)
 * @file        : http.cpp
 * @created     : Thursday Dec 17, 2020 22:39:31 +04
 */

#include <stdexcept>
#include <string>
#include <curl/curl.h>
#include <http/http.h>

namespace vk
{
    nlohmann::ordered_json Http::GET(std::string url)
    {
        std::string response;

        CURL* handle = curl_easy_init();

        if(handle)
        {
            curl_easy_setopt(handle, CURLOPT_URL, url.c_str());
            curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, this->get_write);
            curl_easy_setopt(handle, CURLOPT_WRITEDATA, &response);
            CURLcode res = curl_easy_perform(handle);

            if(res != CURLE_OK)
            {
                std::string err = "GET fail: ";
                err += curl_easy_strerror(res);
                throw std::runtime_error(err);
            }

            curl_easy_cleanup(handle);
        }
        else
        {
            throw std::runtime_error("Handle create error");
        }

        return nlohmann::json::parse(response);
    }

    size_t Http::get_write(char* ptr, size_t size, size_t nmemb, std::string* data)
    {
        if(data)
        {
            size_t r = size * nmemb;

            data->append(ptr, r);
            return r;
        }
        else
        {
            return 0;
        }
    }
}
