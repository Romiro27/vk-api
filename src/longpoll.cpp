/**
 * @author      : romiro27 (vanno6521@gmail.com)
 * @file        : longpoll.cpp
 * @created     : Sunday Dec 20, 2020 22:24:28 +04
 */

#include <api.h>
#include <longpoll.h>
#include <json/json.hpp>

namespace vk
{
    Longpoll::Longpoll(Api &vkapi, int gid)
    {
        this->api      = vkapi;
        this->group_id = gid;

        this->create_longpoll(gid);
    }

    void Longpoll::create_longpoll(int gid)
    {
        nlohmann::ordered_json resp = this->api.method("groups.getLongPollServer",
            {
                { "group_id", gid }
            });

        if(!(resp.find("error") != resp.end()))
        {
            this->session.key = resp.at("response").at("key");
            this->session.server = resp.at("response").at("server");
            this->session.ts = resp.at("response").at("ts");
        }
        else
        {
            std::string err = "Longpoll create fail: ";
            err += resp.at("error").at("error_msg");
            throw std::runtime_error(err);
        }
    }
}
