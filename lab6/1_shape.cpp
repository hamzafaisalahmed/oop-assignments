#include <iostream>
#include <string>
using namespace std;

class Shape
{
protected:
    string color;
    // not accessible in main but can be accessed in circle
public:
    void displayColor()
    {
        cout << "Color: " << color << endl;
    }
    void setColor(string c)
    {
        color = c;
    }
};

class Circle : public Shape
{
private:
    double radius;
    // not accessible anywhere else other than circle
public:
    void area() { cout << "Area: " << 3.14159 * radius * radius << endl; }
    void setRadius(double r) { radius = r; }
};

int main()
{
    Circle c;
    c.setColor("Red");
    // accessed as public in circle and shape was inheritted publicly
    c.setRadius(2.0);
    // public in circle
    c.displayColor();
    // public in circle and shape was in public inheritence
    c.area();
    // public in circle
}