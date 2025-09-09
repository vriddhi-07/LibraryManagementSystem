#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Class declarations
class Book;
class Member;
class Librarian;
class Library;

// User class
class User
{
    protected:
        string userID;
        string name;
        string email;
        string phone;

    public:
        // constructor
        User(string id, string n, string e, string p)
        {
            userID = id;
            name = n;
            email = e;
            phone = p;
        }

        virtual void login()
        {
            cout << name << " logged in sucessfully" << endl;
        }

        string getName() const
        {
            return name;
        }
};

// Book class
class Book
{
    private:
        string bookID;
        string title;
        string author;
        string publisher;
        bool isAvailable;

    public:
        // constructor
        Book(string id, string t, string a, string p)
        {
            bookID = id;
            title = t;
            author = a;
            publisher = p;
            isAvailable = true;
        }

        bool checkAvailability() const
        {
            return isAvailable;
        }

        void updateAvailability(bool status)
        {
            isAvailable = status;
        }

        string getTitle() const
        {
            return title;
        }
};

// Librarian class
class Librarian : public User
{
    public:
        // constructor
        Librarian(string id, string n, string e, string p) : User(id, n, e, p)
        {
        }

        void addBook(Library& lib, Book* book);
        void removeBook(Library& lib, Book* book);
};

// Library class
class Library
{
    private:
        string libraryName;
        vector<Book*> books;
        vector<Member*> members;
        vector<Librarian*> librarians;

    public:
        // constructor
        Library(string name)
        {
            libraryName = name;
        }

        void addLibrarian(Librarian* librarian)
        {
            librarians.push_back(librarian);
            cout << "Librarian added successfully: " << librarian->getName() << endl;
        }

        void removeLibrarian(Librarian* librarian)
        {
            for (auto it = librarians.begin(); it != librarians.end(); ++it)
            {
                if (*it == librarian)
                {
                    librarians.erase(it);
                    cout << "Librarian removed successfully: " << librarian->getName() << endl;
                    return;
                }
            }
            cout << "Librarian not found" << endl;
        }

        vector<Book*>& getBooks()
        {
            return books;
        }

        vector<Member*>& getMembers()
        {
            return members;
        }
};

void Librarian::addBook(Library& lib, Book* book)
{
    lib.getBooks().push_back(book);
    cout << "Book added by " << name << ": " << book->getTitle() << endl;
}

void Librarian::removeBook(Library& lib, Book* book)
{
    for (auto it = lib.getBooks().begin(); it != lib.getBooks().end(); ++it)
    {
        if (*it == book)
        {
            lib.getBooks().erase(it);
            cout << "Book removed by " << name << ": " << book->getTitle() << endl;
            return;
        }
    }
    cout << "Book not found in library" << endl;
}

// Member class
class Member : public User
{
    private:
        vector<Book*> borrowedBooks;

    public:
        // constructor
        Member(string id, string n, string e, string p) : User(id, n, e, p)
        {
        }

        void borrowBook(Book* book)
        {
            if (book->checkAvailability())
            {
                borrowedBooks.push_back(book);
                book->updateAvailability(false);
                cout << name << " successfully borrowed: " << book->getTitle() << endl;
            }

            else
            {
                cout << "Book " << book->getTitle() << " is not available to be borrowed by " << name << endl;
            }
        }

        void returnBook(Book* book)
        {
            for (auto it = borrowedBooks.begin(); it != borrowedBooks.end(); ++it)
            {
                if (*it == book)
                {
                    borrowedBooks.erase(it);
                    book->updateAvailability(true);
                    cout << name << " successfully returned: " << book->getTitle() << endl;
                    return;
                }
            }
            cout << "Book not found in borrowed list" << endl;
        }

        void registerMember(Library& lib)
        {
            lib.getMembers().push_back(this);
            cout << name << " successfully registered as a new member" << endl;
        }
};

// Main function
int main()
{
    Library lib("Central Library");

    // Create librarians
    cout << "------- Add Librarians -------" << endl;
    Librarian* lib1 = new Librarian("L1", "Alice", "alice@lib.com", "1234567890");
    lib.addLibrarian(lib1);

    Librarian* lib2 = new Librarian("L2", "Luna", "luna@lib.com", "789012345");
    lib.addLibrarian(lib2);
    cout << "\n";

    // Create books
    Book* b1 = new Book("B1", "Harry Potter", "JK Rowling", "Penguin");
    Book* b2 = new Book("B2", "Five Survive", "Holly Jackson", "Electric Monkey");
    Book* b3 = new Book("B3", "Six of Crows", "Leigh Bardugo", "Holt & Co");

    // Librarians add books to library
    cout << "------- Librarians add books to library -------" << endl;
    lib1->addBook(lib, b1);
    lib1->addBook(lib, b2);
    lib2->addBook(lib, b3);
    cout << "\n";

    // Create members
    cout << "------- Register members -------" << endl;
    Member* m1 = new Member("M1", "Monica", "monica@mail.com", "9876543210");
    Member* m2 = new Member("M2", "Pip", "pip@gmail.com", "7314710641");
    m1->registerMember(lib);
    m2->registerMember(lib);
    cout << "\n";

    // Members log in, borrow and return books
    cout << "------- Members log in, borrow and return books -------" << endl;
    m1->login();
    m1->borrowBook(b1);
    m1->borrowBook(b2);
    m2->login();
    m2->borrowBook(b1);
    m1->returnBook(b1);
    m2->borrowBook(b1);
    m1->returnBook(b2);
    cout << "\n";

    // librarian removes book from library
    cout << "------- Librarian removes book from library -------" << endl;
    lib2->removeBook(lib, b3);
    cout << "\n";

    // remove librarian
    cout << "------- Remove Librarian -------" << endl;
    lib.removeLibrarian(lib2);
    cout << "\n";

    return 0;
}