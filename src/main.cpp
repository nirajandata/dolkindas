#include "../lib/commands.hpp"
#include "../lib/getenv.hpp"
#include <dpp/dpp.h>
// #include <cstdlib>

int main() {

    //   std::system("ls ");

    std::map<std::string, std::string> TOKENS = get_env_fromFile();

    dpp::cluster bot(TOKENS["BOT"],
                     dpp::i_default_intents | dpp::i_message_content);

    bot.on_log(dpp::utility::cout_logger());

    bot.on_ready([&bot](const dpp::ready_t &event) {
        bot.set_presence(dpp::presence(dpp::ps_online, dpp::at_listening,
                                       "Satlok Ashram Youtube Channel"));
    });

    bot.on_slashcommand([&bot](const dpp::slashcommand_t &event) {
        dpp::command_interaction cmd_data = event.command.get_command_interaction();
        auto command_iter = commands::cmd.find(cmd_data.name);
        if (command_iter != commands::cmd.end()) {
            command_iter->second.func(bot, event);
        }
    });
    bot.on_message_create([&bot, &TOKENS](const dpp::message_create_t &event) {
        if (event.msg.author.is_bot()) {
            return;
        }

        if (event.msg.channel_id == TOKENS["CF_ID"] && !event.msg.content.empty()) {
            dpp::embed embed = dpp::embed()
                    .set_color(dpp::colors::sti_blue)
                    .set_title("Confession")
                    .set_description(event.msg.content)
                    .set_timestamp(time(nullptr));

            bot.message_delete(event.msg.id, event.msg.channel_id);
            bot.message_create(dpp::message(event.msg.channel_id, embed));

        } else if ((int)event.msg.content.find("!em") == 0 &&
                   event.msg.content.size() > 2) {

            dpp::webhook wh(TOKENS["HOOK"]);
            wh.name = event.msg.author.username;
            wh.avatar = event.msg.author.get_avatar_url();
            std::string val = event.msg.content;
            val.erase(0, 3);
            bot.execute_webhook(wh, dpp::message(val));
            bot.message_delete(event.msg.id, event.msg.channel_id);

        } else if (event.msg.content.find("$$") == 0 &&
                   event.msg.content.size() > 3) {
            std::string latex_msg = event.msg.content;
            latex_msg.erase(0, 2);
            latex_msg.erase(latex_msg.length() - 2);
            latex_msg.erase(std::remove(latex_msg.begin(), latex_msg.end(), ' '),
                            latex_msg.end());
            latex_msg = TOKENS["API"] + latex_msg;
            bot.message_create(dpp::message(event.msg.channel_id, latex_msg));
        }
    });

    bot.start(dpp::st_wait);
}
