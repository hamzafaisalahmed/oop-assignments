// Multiple Inheritance] Implement a Car class that inherits from both Vehicle and Engine, where
// both inherit from PoweredSystem. Solve the diamond problem with virtual inheritance.

#include <iostream>

using namespace std;

class PoweredSystem
{
protected:
    int power;

public:
    PoweredSystem() : power(0)
    {
        cout << "PoweredSystem constructor called" << endl;
    }
};

class Vehicle : virtual public PoweredSystem
{
protected:
    int speed;

public:
    Vehicle() : speed(0)
    {
        cout << "Vehicle constructor called" << endl;
        power = 100;
    }
};
class Engine : virtual public PoweredSystem
{
protected:
    int torque;

public:
    Engine() : torque(0)
    {
        cout << "Engine constructor called" << endl;
        power = 200;
    }
    void getPower()
    {
        cout << "Power: " << power << endl;
    }
};

class Car : virtual public Engine, virtual public Vehicle
{
public:
    Car()
    {
        cout << "Car constructor called" << endl;
    }
};

int main()
{
    Car myCar;
    myCar.getPower();
    return 0;
}