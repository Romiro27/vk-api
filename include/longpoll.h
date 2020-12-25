/**
 * @author      : romiro27 (vanno6521@gmail.com)
 * @file        : longpoll.h
 * @created     : Sunday Dec 20, 2020 22:24:09 +04
 */

#pragma once

#include <api.h>
#include <iostream>
#include <thread>
#include <mutex>
#include <json/json.hpp>
#include <http/http.h>

namespace vk
{
    class Longpoll
    {
        public:
            Longpoll(Api &vkapi, int gid);

            void get_settings();
            void set_settings(nlohmann::ordered_json settings);

            template<typename T>
            void handler(T user_query)
            {
                std::lock_guard<std::mutex> lock(this->mute);
                
                if(this->is_update == 1)
                {
                    user_query();
                    this->is_update = 0;
                }
            }

            nlohmann::ordered_json settings;
            nlohmann::ordered_json event = { {"event_id", "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"} };

        private:
            bool is_update;

            int group_id;
            Api api;
            Http HTTP;

            nlohmann::ordered_json session;

            void get_session(int gid);

            std::thread lp;
            std::mutex mute;
            void longpoll();
    };
}
