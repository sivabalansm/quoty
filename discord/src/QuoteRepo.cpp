#include "QuoteRepo.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>

void QuoteRepo::addQuote(std::string quote) {
        quotes.push_back(quote);
}

bool QuoteRepo::removeQuote(std::string quote) {
        std::vector<std::string>::iterator it = findIteratorQuote(quote);
        if (it != quotes.end()) {
                quotes.erase(it);
                return true;
        }
        return false;
}

std::vector<std::string> QuoteRepo::getQuotes() {
        return quotes;
}

bool QuoteRepo::isQuote(std::string quote) {
        if (findIteratorQuote(quote) != quotes.end())
                return true;
        return false;
}

std::string QuoteRepo::getRandomQuote() {
        srand(time(0));
        size_t size = quotes.size();
        if (size > 0) {
                size_t idx = rand() % size;
                return quotes[idx];
        }
        return "";
}
                
std::vector<std::string>::iterator QuoteRepo::findIteratorQuote(std::string quote) {
        std::vector<std::string>::iterator it = std::find(quotes.begin(), quotes.end(), quote);
        return it;
}

