#pragma once
#include <dpp/appcommand.h>
#include <dpp/dpp.h>
#include <functional>
#include <map>
#include <vector>
#include <dpp/nlohmann/json.hpp>

using json = nlohmann::json;

// export module comamnds:slash;

//don't ask me why i didn't use std::function here, i don't like doing dynamic alloc. when not needed
using cmdFunc = void (*)(dpp::cluster &, const dpp::slashcommand_t &);

namespace commands {
    struct cmdType {
        std::string description;
        cmdFunc func;
        std::vector<dpp::command_option> parameters = {};
    };


    inline void ping(dpp::cluster &client, const dpp::slashcommand_t &event) {
        event.reply("ping");
    }
    /*
    inline std::string test(const dpp::http_request_completion_t &cc){
        std::string d="nira";
        d=cc.body;
        std::cout << d;
        return cc.body;
    }*/
    inline void dog(dpp::cluster &client, const dpp::slashcommand_t &event) {
        string dog_image="Error, not found";
      //  client.request("https://dog.ceo/api/breeds/image/random", dpp::m_get,test);
        dpp::http_request_completion_t result = co_await event.from->creator->co_request("https://dog.ceo/api/breeds/image/random", dpp::m_get);
        if(result.status==200){
         json data=json.parse(result.body);
         dog_image=data["message"];
        }
        event.reply(dog_image);

    }
    inline void cat(dpp::cluster &client, const dpp::slashcommand_t &event) {
        event.reply("meow");
    }
    static std::map<std::string, cmdType> cmd = {
            {"ping", {"A ping command", dog}},
            {"dog ",{"Pictures of dog", dog}}
    };

    inline void slash_entry(dpp::cluster &bot) {
        if (dpp::run_once<struct bulk_register>()) {
            std::vector<dpp::slashcommand> allCmd;
            for (auto &t : cmd) {
                dpp::slashcommand temp;
                temp.set_name(t.first).set_application_id(bot.me.id).set_description(
                        t.second.description);
                temp.options = t.second.parameters;
                // todo: std::move
                allCmd.push_back(temp);
            }
            bot.global_bulk_command_create(allCmd);
        }
    }
}