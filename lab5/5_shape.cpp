#include <iostream>
#include <cmath>
using namespace std;

class Shape
{
public:
    virtual double calculateArea()
    {
        cout << "Calculating area of a shape." << endl;
        return -1;
    }
};
class Rectangle : public Shape
{
protected:
    double width;
    double length;

public:
    Rectangle(int l, int w)
    {
        length = l;
        width = w;
    }
    double calculateArea() override
    {
        return length * width;
    }
};
class Circle : public Shape
{
protected:
    double radius;

public:
    Circle(int r)
    {
        radius = r;
    }
    double calculateArea() override
    {
        return 3.14 * radius * radius;
    }
};
class Triangle : public Shape
{
protected:
    double a;
    double b;
    double c;

public:
    Triangle(int a, int b, int c)
    {
        this->a = a;
        this->b = b;
        this->c = c;
    }

    double calculateArea() override
    {
        double s = (a + b + c) / 2;
        return sqrt(s * (s - a) * (s - b) * (s - c));
    }
};

int main()
{
    cout << "Enter number of sides: ";
    int sides;
    cin >> sides;
    Shape *pointer;
    if (sides == 1)
    {
        cout << "Enter radius: ";
        int r;
        cin >> r;
        pointer = new Circle(r);
        cout << "Area of circle: " << pointer->calculateArea() << endl;
    }
    else if (sides == 3)
    {
        cout << "Enter sides: ";
        int a, b, c;
        cin >> a >> b >> c;
        pointer = new Triangle(a, b, c);
        cout << "Area of triangle: " << pointer->calculateArea() << endl;
    }
    else if (sides == 4 || sides == 2)
    {
        cout << "Enter length and width: ";
        int l, w;
        cin >> l >> w;
        pointer = new Rectangle(l, w);
        cout << "Area of rectangle: " << pointer->calculateArea() << endl;
    }
    else
    {
        cout << "Invalid input." << endl;
        return 0;
    }
    delete pointer;
}