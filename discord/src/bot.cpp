#include <dpp/dpp.h>
#include "QuoteRepo.h"
 

int main() {
        const char* BOT_TOKEN = std::getenv("BOT_TOKEN");
        if (BOT_TOKEN == NULL) {
                std::cout << "$BOT_TOKEN Not defined" << std::endl;
                std::exit(1);
        }

        std::string str(BOT_TOKEN);

        dpp::cluster bot(str);

        bot.on_log(dpp::utility::cout_logger());

        bot.on_slashcommand([](const dpp::slashcommand_t& event) {
                        if (event.command.get_command_name() == "ping") {
                        event.reply("Pong!");
                        }
                        });

        bot.on_ready([&bot](const dpp::ready_t& event) {
                        if (dpp::run_once<struct register_bot_commands>()) {
                        bot.global_command_create(dpp::slashcommand("ping", "Ping pong!", bot.me.id));
                        }
                        });

        bot.start(dpp::st_wait);
}
