/**
 * @author      : romiro27 (vanno6521@gmail.com)
 * @file        : api.h
 * @created     : Friday Dec 18, 2020 02:07:58 +04
 */

#pragma once

#include <string>
#include <json/json.hpp>
#include <curl/curl.h>
#include <http/http.h>

namespace vk
{
    class Api
    {
        public:
            Api();
            Api(std::string token);

            nlohmann::ordered_json method(std::string method, nlohmann::ordered_json request);

        private:
            Http http;

            std::string token;
            std::string api_url = "https://api.vk.com/";
            std::string cur_requset;
            float version = 5.52f;

            std::string url_encode(std::string msg);
            void url_convert(std::string method, nlohmann::ordered_json request);
    };
}
