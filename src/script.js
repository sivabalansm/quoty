class Database {

}

class QuoteRepository {
  #db = null;

  constructor (db) {
    this.db = db;
  }

  getQuote() {}
  addQuote(quote) {}
  removeQuote(quote) {}
}
