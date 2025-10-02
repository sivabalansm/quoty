#include <iostream>
#include "QuoteRepo.h"

int main() {
        QuoteRepo quotes("quote.md");
        for (const std::string &quote : quotes.getQuotes()) {
                std::cout << "quote: " << quote << std::endl;
        }

        std::cout << "randome quote: " << quotes.getRandomQuote() << std::endl;
        

        return 0;
}
