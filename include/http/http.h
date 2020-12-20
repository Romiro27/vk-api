/**
 * @author      : romiro27 (vanno6521@gmail.com)
 * @file        : http.h
 * @created     : Thursday Dec 17, 2020 23:51:00 +04
 */

#pragma once

#include <string>
#include <json/json.hpp>

namespace vk
{
    class Http
    {
        public:
            nlohmann::ordered_json GET(std::string url);

        private:
            static size_t get_write(char *ptr, size_t size, size_t nmemb, std::string* data);
    };
}
