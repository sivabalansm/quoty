#include "QuoteRepo.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <fstream>

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

std::vector<std::string> QuoteRepo::getQuotes() const {
        return quotes;
}

bool QuoteRepo::isQuote(std::string quote) {
        if (findIteratorQuote(quote) != quotes.end())
                return true;
        return false;
}

std::string QuoteRepo::getRandomQuote() const {
        srand(time(0));
        size_t size = quotes.size();
        if (size > 0) {
                size_t idx = rand() % size;
                return quotes[idx];
        }
        return "";
}

void QuoteRepo::saveToFile(std::string filename) {
        std::ofstream file = std::ofstream(filename);
        for (const std::string &quote : quotes) {
                file << quote << "\n";
        }
        file.close();
}
                
void QuoteRepo::loadFromFile(std::string filename) {
        std::ifstream file = std::ifstream(filename);
        if (!file) {
                std::cerr << "File cannot be opened" << std::endl;
                return;
        }
        std::string line;
        while (std::getline(file, line)) { // getline removes new line automatically!
                if (line != "")
                        quotes.push_back(line);
        }
        file.close();
}

QuoteRepo::QuoteRepo(std::string filename) {
        loadFromFile(filename);
}

QuoteRepo::QuoteRepo(std::vector<std::string> quotes) {
        quotes = quotes;
}

std::vector<std::string>::iterator QuoteRepo::findIteratorQuote(std::string quote) {
        std::vector<std::string>::iterator it = std::find(quotes.begin(), quotes.end(), quote);
        return it;
}

