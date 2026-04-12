#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Book{
    private:
    string title;
    int code;
    int price;
    vector <float> reviews;
    public:
    void review(float grd){
        reviews.push_back(grd);
    }
    int getCode(){
        return code;
    }
    int getPrice(){
        return price;
    }
    float getScore(){
        float scores = 0;
        for (int i = 0; i < reviews.size(); i++){
            scores += reviews[i];
        }
        if (reviews.size() == 0) return 0;
        else return scores/reviews.size();
    }
    Book(string x, int y, int z){
        title = x;
        code = y;
        price = z;
    }
};





int main() {
Book books[5] = {
Book("The C\texttt{++} Programming Language", 1, 60),
Book("The Mythical Man-month", 2, 40),
Book("The Pragmatic Programmer: Your Journey to Mastery", 3, 50),
Book("The Art of Computer Programming", 4, 50),
Book("C\texttt{++} For Dummies", 5, 30)
};
books[0].review(5);
books[0].review(4);
books[1].review(4);
books[2].review(2);
books[3].review(5);
int code;
cout << "Enter code: ";
cin >> code;
for (int i = 0; i < 5; i++) {
if (books[i].getCode() == code) {
if (books[i].getScore() == 0) {
cout << "The book has not been graded yet" << endl;
} else {
cout << "The book has score " << books[i].getScore() << " and price " <<
books[i].getPrice() << endl;
}
return 0;
}
}
cout << "The book does not exist" << endl;
return 0;
}

