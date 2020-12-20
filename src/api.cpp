/**
 * @author      : romiro27 (vanno6521@gmail.com)
 * @file        : api.cpp
 * @created     : Friday Dec 18, 2020 02:07:36 +04
 */

#include <string>
#include <api.h>
#include <json/json.hpp>
#include <curl/curl.h>
#include <http/http.h>

namespace vk
{
    Api::Api()
    {
    }

    Api::Api(std::string token)
    {
        this->token = token;
    }

    nlohmann::ordered_json Api::method(std::string method, nlohmann::ordered_json request)
    {
        this->url_convert(std::string("method/") + method, request);

        nlohmann::ordered_json ret = this->http.GET(cur_requset);

        this->cur_requset.clear();

        return ret;
    }

    std::string Api::url_encode(std::string msg)
    {
        CURL* handle = curl_easy_init();

        msg = curl_easy_escape(handle, msg.c_str(), msg.length());

        curl_easy_cleanup(handle);

        return msg;
    }

    void Api::url_convert(std::string method, nlohmann::ordered_json request)
    {
        this->cur_requset = this->api_url + method + "?";

        uint64_t buff = 0u;

        for(auto it = request.begin(); it != request.end(); ++it)
        {
            if(it->is_number())
            {
                buff = *it;
                this->cur_requset += it.key() + '=' + std::to_string(buff);
                this->cur_requset += '&';
                buff = 0;
            }
            else
            {
                this->cur_requset += it.key() + '=' + this->url_encode(it.value());
                this->cur_requset += '&';
            }
        }

        this->cur_requset += "v=" + std::to_string(this->version);
        this->cur_requset += "&access_token=" + this->token;
    }
}
