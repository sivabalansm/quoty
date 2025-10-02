#ifndef QUOTEFACTORY_H
#define QUOTEFACTORY_H
#include <vector>
#include <iostream>

class QuoteRepo {
        private:
                void addQuote(std::string quote);

                bool removeQuote(std::string quote);

                std::vector<std::string> getQuotes();

                bool isQuote(std::string quote);

                std::string getRandomQuote();

                static std::vector<std::string> loadFromFile(std::string filename);

                static std::vector<std::string> saveToFile(std::string filename);

        private:
                std::vector<std::string> quotes;
                std::vector<std::string>::iterator findIteratorQuote(std::string quote);
};

#endif
