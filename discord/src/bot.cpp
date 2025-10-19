#include <dpp/dpp.h>
#include "QuoteRepo.h"
 
int main() {
        // Setup quotes from file
        std::string filename = "quote.md";
        QuoteRepo quotes(filename);
        std::cout << "Random quote test: " << quotes.getRandomQuote() << std::endl;

        // Read token from env vars, else crash
        const char* BOT_TOKEN = std::getenv("BOT_TOKEN");
        if (BOT_TOKEN == NULL) {
                std::cout << "$BOT_TOKEN Not defined" << std::endl;
                std::exit(1);
        }
        std::string str(BOT_TOKEN);

        /***************************************** Starting Bot setup *****************************************/
        dpp::cluster bot(str);

        // Simple logging
        bot.on_log(dpp::utility::cout_logger());

        // Add slash commands
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

        // Setup before bot starts
        bot.on_ready([&bot](const dpp::ready_t& event) {
                        if (dpp::run_once<struct register_bot_commands>()) {
                                bot.global_command_create(dpp::slashcommand("randomquote", "Get a random quote!", bot.me.id));
                                bot.global_command_create(dpp::slashcommand("addquote", "Add a quote to your quotebook", bot.me.id).add_option(dpp::command_option(dpp::co_string, "quote", "new quote you would like to add", true)));
                        }
        });

        std::cout << "Starting bot" << std::endl;
        bot.start(dpp::st_return);

        // Might as well implement my own timer
        while (true) {
                std::time_t now = std::time(NULL);
                struct tm *datetimeRN = localtime(&now);
                // convert to est time from utc
                datetimeRN->tm_hour -= 4;
                if (datetimeRN->tm_hour == 9) {
                        quotes.loadFromFile(filename);
                        bot.message_create(dpp::message(1066927523197370390, quotes.getRandomQuote()));
                }
                struct tm datatimeTMR = *datetimeRN;
                datatimeTMR.tm_mday += 1;
                datatimeTMR.tm_hour = 9;
                datatimeTMR.tm_min = 0;
                datatimeTMR.tm_sec = 0;

                int secondsToWait = std::difftime(std::mktime(&datatimeTMR), std::mktime(datetimeRN));

                std::this_thread::sleep_for(std::chrono::seconds(secondsToWait));
        }
}
