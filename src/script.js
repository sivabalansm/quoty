import { initializeApp } from "https://www.gstatic.com/firebasejs/12.0.0/firebase-app.js";
import { getFirestore, collection, getDocs } from "https://www.gstatic.com/firebasejs/12.0.0/firebase-firestore.js";
// import { getFirestore, collection, addDoc, getDocs } from "https://www.gstatic.com/firebasejs/12.0.0/firebase-app.js";

const firebaseConfig = { };


  // Initialize Firebase

const app = initializeApp(firebaseConfig);

const db = getFirestore(app)
const userCollection = collection(db, "quotes");
const docs = await getDocs(userCollection);
console.log(docs.forEach((doc) => {
  console.log(`${doc.id} =>`, doc.data());
}));




class UserDatabase {
  static instance = null;
  constructor() {
    if (UserDatabase.instance) {
      return UserDatabase.instance;
    }
    UserDatabase.instance = this;
  }

  connect() {}

}

class QuoteRepository {
  #db = null;
  #quotes = [];

  constructor(db) {
    this.db = db;
  }

  getQuote() {}

  addQuote(quote) {
    this.#db.addItem();
  }

  removeQuote(quote) {}
}

class RepositoryFactory {
  static createQuoteRepository() {
    const db = new UserDatabase();
    return new QuoteRepository(db);
  }
}


const userQuoteRepo = RepositoryFactory.createQuoteRepository();

// Get quote
const addQuoteButton = document.getElementById("new-quote-button");
addQuoteButton.addEventListener("click", () => {
  const quoteInput = document.getElementById("new-quote-field");

  userQuoteRepo.addQuote(quoteInput.value);
  quoteInput.value = ''

});
