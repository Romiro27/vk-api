/**
 * @author      : romiro27 (vanno6521@gmail.com)
 * @file        : longpoll.cpp
 * @created     : Sunday Dec 20, 2020 22:24:28 +04
 */

#include <api.h>
#include <string>
#include <thread>
#include <mutex>
#include <longpoll.h>
#include <json/json.hpp>
#include <http/http.h>

namespace vk
{
    Longpoll::Longpoll(Api &vkapi, int gid)
    {
        this->api      = vkapi;
        this->group_id = gid;

        this->get_session(gid);

        this->lp = std::thread(&Longpoll::longpoll, this);
        this->lp.detach();
    }

    void Longpoll::get_session(int gid)
    {
        nlohmann::ordered_json resp = this->api.method("groups.getLongPollServer",
            {
                { "group_id", gid }
            });

        if(!(resp.find("error") != resp.end()))
        {
            this->session = resp.at("response");
        }
        else
        {
            std::string err = "Longpoll create fail: ";
            err += resp.at("error").at("error_msg");
            throw std::runtime_error(err);
        }
    }

    void Longpoll::get_settings()
    {
        this->settings = this->api.method("groups.getLongPollSettings",
            {
                { "group_id:", this->group_id }
            });
    }

    void Longpoll::set_settings(nlohmann::ordered_json settings)
    {
        this->api.method("groups.setLongPollSettings", settings);

        this->get_settings();
    }

    void Longpoll::longpoll()
    {
        for(;;)
        {
            nlohmann::ordered_json resp = this->HTTP.GET(
                this->session.at("server").get<std::string>() +
                "?act=a_check&key=" +
                this->session.at("key").get<std::string>() +
                "&ts=" +
                this->session.at("ts").get<std::string>() +
                "&wait=25"
            );

            std::lock_guard<std::mutex> lock(this->mute);

            if(this->event.at("event_id") != resp.at("updates")[0]["event_id"])
            {
                this->is_update = true;

                this->session.at("ts") = resp.at("ts");
                this->event = resp.at("updates")[0];
            }
        }
    }
}
