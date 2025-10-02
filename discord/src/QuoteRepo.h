#ifndef QUOTEFACTORY_H
#define QUOTEFACTORY_H
#include <vector>
#include <iostream>

class QuoteRepo {
        public:
                void addQuote(std::string quote);

                bool removeQuote(std::string quote);

                std::vector<std::string> getQuotes() const;

                bool isQuote(std::string quote);

                std::string getRandomQuote() const;

                void loadFromFile(std::string filename);

                void saveToFile(std::string filename);

                QuoteRepo(std::vector<std::string> quotes);
                QuoteRepo(std::string filename);

        private:
                std::vector<std::string> quotes;
                std::vector<std::string>::iterator findIteratorQuote(std::string quote);
};

#endif
