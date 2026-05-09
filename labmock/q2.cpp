#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <iomanip>
using namespace std;

class Book
{
protected:
    string title;
    string author;
    double price;

public:
    Book(string t, string a, double p) : title(t), author(a)
    {
        if (p < 0)
            throw invalid_argument("Price cannot be negative");
        else
            price = p;
    }
    virtual void display() const = 0;
    virtual ~Book() = default;
    std::string getTitle() const { return title; }
    double getPrice() const { return price; }
};

class PhysicalBook : public Book
{
    int pageCount;

public:
    PhysicalBook(std::string title, std::string author, double price,
                 int pageCount) : Book(title, author, price), pageCount(pageCount) {}
    void display() const override
    {
        cout << fixed << setprecision(2) << " [Physical] " << title << "by " << author << "| Price: $" << price << " | Pages: " << pageCount << endl;
    }
};

class EBook : public Book
{
    double fileSizeMB;

public:
    EBook(std::string title, std::string author, double price, double fileSizeMB) : Book(title, author, price), fileSizeMB(fileSizeMB) {}
    void display() const override
    {
        cout << fixed << setprecision(2) << " [EBook] " << title << "by " << author << "| Price: $" << price << " | Size: " << fileSizeMB << " MB " << endl;
    }
};

class Library
{
    std::vector<Book *> books;

public:
    void addBook(Book *b)
    {
        if (b)
            books.push_back(b);
    }
    void removeBook(const std::string &title)
    {
        for (int i = 0; i < books.size(); i++)
        {
            if (title == books[i]->getTitle())
            {
                delete books[i];
                books.erase(books.begin() + i);
                cout << "Removed " << title << endl;
                return;
            }
        }
        cout << "Not found: " << title << endl;
    }
    void displayAll() const
    {
        if (books.size() == 0)
            cout << "Library is empty\n";
        for (auto book : books)
        {
            book->display();
        }
    }
    void displayAbovePrice(double threshold) const
    {
        auto func = [threshold](int x)
        { return x > threshold; };
        bool flag = false;
        for (auto book : books)
        {
            if (func(book->getPrice()))
            {
                book->display();
                flag = true;
            }
        }
        if (!flag)
            cout << "No books above $" << threshold << endl;
    }
};

int main()
{
    Library lib;
    lib.addBook(new PhysicalBook("The Pragmatic Programmer",
                                 "Hunt & Thomas", 45.99, 352));
    lib.addBook(new EBook("Clean Code",
                          "Robert Martin", 29.99, 3.5));
    lib.addBook(new PhysicalBook("Introduction to Algorithms",
                                 "CLRS", 89.99, 1292));
    lib.addBook(new EBook("Design Patterns",
                          "Gang of Four", 39.99, 5.2));
    lib.addBook(new PhysicalBook("The Mythical Man-Month",
                                 "Fred Brooks", 19.99, 336));
    lib.addBook(new EBook("Effective Modern C++",
                          "Scott Meyers", 34.99, 2.8));
    std::cout << "=== All Books ===" << std::endl;
    lib.displayAll();
    std::cout << "\n=== Books above $35.00 ===" << std::endl;
    lib.displayAbovePrice(35.0);
    std::cout << "\n=== Removing ’Clean Code’ ===" << std::endl;
    lib.removeBook("Clean Code");
    std::cout << "\n=== Removing ’Nonexistent Book’ ===" << std::endl;
    lib.removeBook("Nonexistent Book");
    std::cout << "\n=== Remaining Books ===" << std::endl;
    lib.displayAll();
    std::cout << "\n=== Testing exception for negative price ===" << std::endl;
    try
    {
        Book *bad = new PhysicalBook("Bad Book", "No Author", -5.00, 100);
        lib.addBook(bad);
    }
    catch (const std::invalid_argument &e)
    {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }
    return 0;
}