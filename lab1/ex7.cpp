#include <iostream>

using namespace std;

class Book
{
    string name;
    string ISBN;
    string author;
    string publisher;

public:
    string getName() { return name; }
    string getISBN() { return ISBN; }
    string getAuthor() { return author; }
    string getPublisher() { return publisher; }
    void setName(string n) { name = n; }
    void setISBN(string isbn) { ISBN = isbn; }
    void setAuthor(string a) { author = a; }
    void setPublisher(string p) { publisher = p; }

    string getBookInfo()
    {
        return "Name: " + name + ", ISBN: " + ISBN + ", Author: " + author + ", Publisher: " + publisher;
    }
    Book(string n, string isbn, string a, string p)
    {
        name = n;
        ISBN = isbn;
        author = a;
        publisher = p;
    }
};

int main()
{
    Book one = Book("Book1", "ISBN1", "Author1", "Publisher1");
    Book two = Book("Book2", "ISBN2", "Author2", "Publisher2");
    Book three = Book("Book3", "ISBN3", "Author3", "Publisher3");
    Book four = Book("Book4", "ISBN4", "Author4", "Publisher4");
    Book five = Book("Book5", "ISBN5", "Author5", "Publisher5");
    Book array[5] = {one, two, three, four, five};

    for (int i = 0; i < 5; i++)
    {
        cout << array[i].getBookInfo() << endl;
    }
}