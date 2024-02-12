//
// Created by kira on 1/4/24.
//
/*
#include "commands.hpp"

namespace commands{

    void dog(dpp::cluster &client, const dpp::slashcommand_t &event) {

    }
    void latex(dpp::cluster &client,const dpp::slashcommand_t &event){
        auto parameter=event.get_parameter("code");
        if(std::holds_alternative<std::string>(parameter)){
           std::string val="https://latex.codecogs.com/png.image?\huge&space;\dpi{200}\bg{black}&space;"
                                                      +std::get<std::string>(parameter);
           event.reply(val);
        }
    }
}
 */


