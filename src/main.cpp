#include <dpp/dpp.h>
#include "token.h"

int main() {
    /*
    std::ifstream env;
    std::string BOT_TOKEN;
    env.open(".env");
    env>>BOT_TOKEN;
    env.close();
 */
    const std::string BOT_TOKEN=ENV_TOKEN;
//    const int64_t CID=ENV_CID;

    dpp::cluster bot(BOT_TOKEN, dpp::i_default_intents | dpp::i_message_content);

    bot.on_log(dpp::utility::cout_logger());

    bot.on_message_create([&bot](const dpp::message_create_t & event) {
        if (event.msg.channel_id== ENV_CID && event.msg.content.size()>0) {
            dpp::embed embed = dpp::embed().
                    set_color(dpp::colors::sti_blue).
                    set_title("Confession").
                    set_description(event.msg.content).
                    set_timestamp(time(0));

            bot.message_delete(event.msg.id,event.msg.channel_id);
            bot.message_create(dpp::message(event.msg.channel_id,embed));
        }
    });

   bot.start(dpp::st_wait);
}