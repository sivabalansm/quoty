import { initializeApp } from "https://www.gstatic.com/firebasejs/12.0.0/firebase-app.js";
import { getFirestore, collection, getDoc, doc, addDoc, updateDoc, deleteField } from "https://www.gstatic.com/firebasejs/12.0.0/firebase-firestore.js";
import { convertToHash } from "./utils.js";
import { FIREBASECONFIG } from "./config.js";

class UserDatabase {
  static instance = null;
  collectionName = "quotes";
  db = null;
  userCollection = null;
  constructor() {
    if (UserDatabase.instance) {
      return UserDatabase.instance;
    }
    UserDatabase.instance = this;
    this.connect();
  }

  connect() {
          // Initialize Firebase
        const app = initializeApp(FIREBASECONFIG);
        this.db = getFirestore(app);
        this.userCollection = collection(this.db, this.collectionName);
  }
  
  async get(documentName) {
        const queriedDoc = await getDoc(doc(this.userCollection, documentName));
        if (queriedDoc.exists())
                return queriedDoc.data();
        return null;
  }

  async add(documentName, data) {
        await updateDoc(doc(this.userCollection, documentName), data);
  }

  async remove(documentName, field) {
        await updateDoc(doc(this.userCollection, documentName), { [field] : deleteField() });
  }

}

class QuoteRepository {
  #db = null;
  #documentName;
  #quotes = null;

  constructor(db, documentName) {
    this.#db = db;
    this.#documentName = documentName;
    this.#quotes = this.#db.get(this.#documentName);
  }

  getQuotes() {
        return this.#quotes;
  }

  addQuote(quote) {
    const hash = convertToHash(quote);
    this.#db.add(this.#documentName, { [hash] : quote });
  }

  removeQuote(quote) {
    const hash = convertToHash(quote);
    this.#db.remove(this.#documentName, hash);
  }
}

class RepositoryFactory {
  static createQuoteRepository() {
    const db = new UserDatabase();
    return new QuoteRepository(db, "quote_book");
  }
}


const userQuoteRepo = RepositoryFactory.createQuoteRepository();

console.log(await new UserDatabase().get("quote_book"));
console.log(await new UserDatabase().add("quote_book", { "sdfff": "bombo" } ));
console.log(await new UserDatabase().remove("quote_book", "sdfff"));
// Get quote
const addQuoteButton = document.getElementById("new-quote-button");

addQuoteButton.addEventListener("click", () => {
  const quoteInput = document.getElementById("new-quote-field");

  userQuoteRepo.addQuote(quoteInput.value);
  quoteInput.value = ''

});
