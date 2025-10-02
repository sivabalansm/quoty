#include <dpp/dpp.h>
#include "QuoteRepo.h"
 

int main() {
        // setup quotes
        std::string filename = "quote.md";
        QuoteRepo quotes(filename);
        std::cout << "Random quote test: " << quotes.getRandomQuote() << std::endl;

        const char* BOT_TOKEN = std::getenv("BOT_TOKEN");
        if (BOT_TOKEN == NULL) {
                std::cout << "$BOT_TOKEN Not defined" << std::endl;
                std::exit(1);
        }

        std::string str(BOT_TOKEN);

        dpp::cluster bot(str);

        bot.on_log(dpp::utility::cout_logger());

        bot.on_slashcommand([&quotes, &filename](const dpp::slashcommand_t& event) {
                                if (event.command.get_command_name() == "randomquote") {
                                        const std::string quote = quotes.getRandomQuote();
                                        event.reply(quote);
                                }
                                if (event.command.get_command_name() == "addquote") {
                                        std::string newQuote = std::get<std::string>(event.get_parameter("quote"));
                                        quotes.addQuote(newQuote);
                                        quotes.saveToFile(filename);
                                        event.reply("Added quote: " + newQuote);
                                }
                        });

        
        bot.on_ready([&bot, &quotes](const dpp::ready_t& event) {
                        bot.start_timer([&bot, &quotes](const dpp::timer &timer) {
                                                bot.message_create(dpp::message(1066927523197370390, quotes.getRandomQuote()));

                                        }, 10);

                        if (dpp::run_once<struct register_bot_commands>()) {
                                bot.global_command_create(dpp::slashcommand("randomquote", "Get a random quote!", bot.me.id));
                                bot.global_command_create(dpp::slashcommand("addquote", "Add a quote to your quotebook", bot.me.id).add_option(dpp::command_option(dpp::co_string, "quote", "new quote you would like to add", true)));
                        }
                        });

        std::cout << "Starting bot" << std::endl;
        bot.start(dpp::st_wait);
}
