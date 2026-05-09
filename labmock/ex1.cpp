#include <iostream>
#include <string>
using namespace std;

class Vehicle
{
protected:
    string brand;

public:
    Vehicle(const string &brand) : brand(brand) {}
    virtual double topSpeed() const = 0;
    virtual void display() const = 0;

    virtual ~Vehicle() {}
};

class MotorVehicle : public Vehicle
{
protected:
    bool electric;

public:
    MotorVehicle(const string &brand, bool electric) : Vehicle(brand), electric(electric) {}
    virtual bool isElectric() const = 0;
};

class Car : public MotorVehicle
{
private:
    double enginePower;

public:
    Car(const string &brand, bool electric, double enginePower)
        : MotorVehicle(brand, electric), enginePower(enginePower) {}

    double topSpeed() const override
    {
        return enginePower * 2.5;
    }
    bool isElectric() const override
    {
        return electric;
    }
    void display() const override
    {
        cout << "Brand: " << brand << "\nPower: " << enginePower << "\nelectric status: " << isElectric() << endl;
    }
    double operator+(Car const &other)
    {
        return topSpeed() + other.topSpeed();
    }
    friend ostream &operator<<(ostream &os, const Car &car)
    {
        car.display();
        return os;
    }
};

int main()
{
    Vehicle *v1 = new Car("Tesla", true, 300.0);
    Vehicle *v2 = new Car("Ford", false, 450.0);

    cout << "Car 1: " << *(static_cast<Car *>(v1)) << endl;
    cout << "Car 2: " << *(static_cast<Car *>(v2)) << endl;

    Vehicle *vehicles[2] = {v1, v2};
    for (int i = 0; i < 2; ++i)
    {
        MotorVehicle *mv = dynamic_cast<MotorVehicle *>(vehicles[i]);
        if (mv)
        {
            cout << "Vehicle " << i + 1 << " check: "
                 << (mv->isElectric() ? "car is electric." : "car is not electric.")
                 << endl;
        }
    }

    Car *c1 = static_cast<Car *>(v1);
    Car *c2 = static_cast<Car *>(v2);
    double totalSpeed = *c1 + *c2;

    cout << "Combined Top Speed: " << totalSpeed << endl;

    delete v1;
    delete v2;

    return 0;
}