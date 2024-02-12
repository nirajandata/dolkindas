#pragma once
#include <dpp/appcommand.h>
#include <dpp/dpp.h>
#include <functional>
#include <map>
#include <vector>
#include <dpp/nlohmann/json.hpp>


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
    void latex(dpp::cluster &client,const dpp::slashcommand_t &event);
    void dog(dpp::cluster &client, const dpp::slashcommand_t &event);
//        dpp::http_request_completion_t result = co_await event.from->creator->co_request("https://dog.ceo/api/breeds/image/random", dpp::m_get);

    inline void cat(dpp::cluster &client, const dpp::slashcommand_t &event) {
        event.reply("meow");
    }
    static std::map<std::string, cmdType> cmd = {
            {"ping", {"A ping command", ping}},
            {"cat",{"meow meow ", cat}}
    };

    inline void slash_entry(dpp::cluster &bot) {
        if (dpp::run_once<struct bulk_register>()) {
            std::vector<dpp::slashcommand> allCmd;
            for (auto &t : cmd) {
                dpp::slashcommand temp;
                temp.set_name(t.first).set_application_id(bot.me.id).set_description(
                        t.second.description);
                temp.options = t.second.parameters;
                allCmd.push_back(temp);
            }
            bot.global_bulk_command_create(allCmd);
        }
    }
    inline void clear_commands(dpp::cluster &bot){
        if (dpp::run_once<struct clear_bot_commands>()) {
            bot.global_bulk_command_delete();
        }
    }
}