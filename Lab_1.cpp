#include <iostream>
#include <string>

class Book {
    private:
        std::string title;
        std::string author;
        int isbn;

    public:
        Book() : title(""), author(""), isbn(0) {}

        Book(std::string title, std::string author, int isbn) {
            this->title = title;
            this->author = author;
            this->isbn = isbn;
        }

        std::string showBook() const {
            return "Title: " + title + "; Author: " + author + ", ISBN: " + std::to_string(isbn);
        }

        int getISBN() const {
            return isbn;
        }
};

class Library {
    private:
        static const int maxBooks = 50;
        Book books[maxBooks];
        int numBooks;

public:
    Library() {
        numBooks = 0;
    }

    void addBook(const Book& book) {
        if (numBooks < maxBooks) {
            books[numBooks] = book;
            numBooks++;
            std::cout << "The book has been added.\n";
        } else {
            std::cout << "The library is full.\n";
        }
    }

    void removeBook(int isbn) {
        for (int i = 0; i < numBooks; ++i) {
            if (books[i].getISBN() == isbn) {
                for (int j = i; j < numBooks - 1; ++j) {
                    books[j] = books[j + 1];
                }
                numBooks--;
                std::cout << "Book with ISBN: " << isbn << " removed.\n";
                return;
            }
        }
        std::cout << "Book with ISBN: " << isbn << " not found.\n";
    }

    int getNumBooks() const {
        return numBooks;
    }

    const Book* getBooks() const {
        return books;
    }
};

void showBooks(const Library& library) {
    if (library.getNumBooks() == 0) {
        std::cout << "The library is empty.\n";
    } else {
        const Book* books = library.getBooks();
        for (int i = 0; i < library.getNumBooks(); ++i) {
            std::cout << books[i].showBook() << std::endl;
        }
    }
}

void showMenu() {
    std::cout << "\nMenu:\n";
    std::cout << "1. Add a book\n";
    std::cout << "2. Remove a book by ISBN\n";
    std::cout << "3. Show all books\n";
    std::cout << "4. Exit\n";
    std::cout << "Choose an option: ";
}

int main() {
    Library library;
    int option;

    do {
        showMenu();
        std::cin >> option;

        switch (option) {
            case 1: {
                std::string title, author;
                int isbn;
                std::cout << "Enter book title: ";
                std::cin.ignore();
                std::getline(std::cin, title);
                std::cout << "Enter author name: ";
                std::getline(std::cin, author);
                std::cout << "Enter ISBN number: ";
                std::cin >> isbn;

                Book newBook(title, author, isbn);
                library.addBook(newBook);
                break;
            }
            case 2: {
                int isbn;
                std::cout << "Enter ISBN of the book to remove: ";
                std::cin >> isbn;
                library.removeBook(isbn);
                break;
            }
            case 3: {
                std::cout << "Books in the library:\n";
                showBooks(library);
                break;
            }
            case 4: {
                std::cout << "Exiting the program.\n";
                break;
            }
            default: {
                std::cout << "Invalid option, please try again.\n";
                break;
            }
        }

    } while (option != 4);

    return 0;
}
