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
    const std::string BOT_TOKEN=TOKEN_ID;
    const int64_t CID=1093248426076020787;

    dpp::cluster bot(BOT_TOKEN, dpp::i_default_intents | dpp::i_message_content);

    bot.on_log(dpp::utility::cout_logger());

    bot.on_message_create([&bot](const dpp::message_create_t & event) {
        if (event.msg.channel_id== CID && event.msg.content.size()>0) {
            dpp::embed embed = dpp::embed().
                    set_color(dpp::colors::sti_blue).
                    set_title("confession").
                    set_description(event.msg.content).
                    set_timestamp(time(0));

            /* reply with the created embed */
            bot.message_create(dpp::message(event.msg.channel_id,embed));
        }
    });

   bot.start(dpp::st_wait);
}