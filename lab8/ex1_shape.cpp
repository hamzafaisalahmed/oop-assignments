#include <iostream>

using namespace std;

class Shape
{
public:
    virtual double area() = 0;
    virtual ~Shape() {}
};

class Circle : public Shape
{
    double r;

public:
    Circle(double r) : r(r) {}
    double area() override
    {
        return 3.14 * r * r;
    }
};

class Rectangle : public Shape
{
    double width, height;

public:
    Rectangle(double width, double height) : width(width), height(height) {}
    double area() override
    {
        return width * height;
    }
};

class Triangle : public Shape
{
    double base, height;

public:
    Triangle(double base, double height) : base(base), height(height) {}
    double area() override
    {
        return 0.5 * base * height;
    }
};

int main()
{
    Shape *circle = new Circle(5.5);
    Shape *rectangle = new Rectangle(8, 4.2);
    Shape *triangle = new Triangle(6, 3.5);
    cout << "Circle area: " << circle->area() << endl;
    cout << "Rectangle area: " << rectangle->area() << endl;
    cout << "Triangle area: " << triangle->area() << endl;
}