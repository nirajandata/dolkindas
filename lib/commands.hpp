#pragma once
#include <dpp/appcommand.h>
#include <dpp/dpp.h>
#include <functional>
#include <map>
#include <vector>
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
    inline void dog(dpp::cluster &client, const dpp::slashcommand_t &event) {
        event.reply("dog");
    }
    inline void cat(dpp::cluster &client, const dpp::slashcommand_t &event) {
        event.reply("meow");
    }
    static std::map<std::string, cmdType> cmd = {
            {"ping", {"A ping command", ping}},
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