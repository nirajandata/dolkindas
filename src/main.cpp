#include <dpp/dpp.h>
#include "token.h"

int main() {
    /*
    stdifstream env;
    std::string BOT_TOKEN;
    env.open(".env");
    env>>BOT_TOKEN;
    env.close();
 */
    dpp::cluster bot(ENV_TOKEN, dpp::i_default_intents | dpp::i_message_content);

    bot.on_log(dpp::utility::cout_logger());

    bot.on_ready([&bot](const dpp::ready_t & event){
        bot.set_presence(dpp::presence(dpp::ps_online ,dpp::at_listening,"Satlok Ashram Youtube Channel"));
    });
    bot.on_message_create([&bot](const dpp::message_create_t & event) {
        if (event.msg.channel_id== ENV_CID && !event.msg.content.empty()) {
            dpp::embed embed = dpp::embed().
                    set_color(dpp::colors::sti_blue).
                    set_title("Confession").
                    set_description(event.msg.content).
                    set_timestamp(time(nullptr));

            bot.message_delete(event.msg.id,event.msg.channel_id);
            bot.message_create(dpp::message(event.msg.channel_id,embed));
        }
    });

   bot.start(dpp::st_wait);
}