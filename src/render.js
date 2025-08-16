export function renderQuotes(quotes) {
        const quoteList = document.getElementById("quote-list");
        for (const quote of quotes) {
                const quoteContainer = document.createElement("p");
                quoteContainer.innerHTML = quote;
                quoteList.append(quoteContainer);
        }
}
