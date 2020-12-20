/**
 * @author      : romiro27 (vanno6521@gmail.com)
 * @file        : longpoll.h
 * @created     : Sunday Dec 20, 2020 22:24:09 +04
 */

#pragma once

#include <api.h>

namespace vk
{
    class Longpoll
    {
        public:
            Longpoll(Api &vkapi, int gid);

        private:
            int group_id;
            Api api;

            struct _session
            {
                std::string key;
                std::string server;
                std::string ts;
            } session;

            void create_longpoll(int gid);
    };
}
