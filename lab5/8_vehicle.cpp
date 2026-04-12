#include <iostream>
#include <string>
using namespace std;

class Vehicle
{
protected:
    double rentalPricePerDay;
    string vehicleType;

public:
    Vehicle(double price, string type) : rentalPricePerDay(price), vehicleType(type) {}

    virtual double rent(int days) = 0;
    void rent(int days, string paymentMethod)
    {
        double total = rent(days);
        cout << "Total Rental for " << days << " Days: $" << total << endl;
        cout << "Payment Method: " << paymentMethod << endl;
    }
    void rent(int days, double amount)
    {
        double total = rent(days);
        cout << "Total Rental for " << days << " Days: $" << total << endl;
        cout << "Amount Paid: $" << amount << endl;
    }
    virtual void displayInfo()
    {
        cout << "Type: " << vehicleType << endl;
        cout << "Rental price per day: $" << rentalPricePerDay << endl;
    }
    string operator+(Vehicle &other)
    {
        cout << "Comparison of rental costs: " << endl;
        if (rentalPricePerDay > other.rentalPricePerDay)
            return "The " + other.vehicleType + " rental is cheaper than the " + vehicleType + " rental.";
        else
            return "The " + vehicleType + " rental is more expensive than the " + other.vehicleType + " rental.";
    }
    virtual ~Vehicle() {}
};

class Car : public Vehicle
{
protected:
    bool Airconditioning;
    int seats;

public:
    Car(double p, bool ac, int s) : Vehicle(p, "Car"), Airconditioning(ac), seats(s) {}
    double rent(int days) override
    {
        if (days > 7)
            return (rentalPricePerDay * days) * 0.9;
        else
            return (rentalPricePerDay * days);
    }
    void displayInfo() override
    {
        Vehicle::displayInfo();
        cout << "Air conditioning: ";
        if (Airconditioning)
            cout << "Yes" << endl;
        else
            cout << "No" << endl;
        cout << "Seats: " << seats << endl;
    }
};
class Bike : public Vehicle
{
protected:
    bool helmetIncluded;
    string fuelType;

public:
    Bike(double p, bool h, string f) : Vehicle(p, "Bike"), helmetIncluded(h), fuelType(f) {}
    double rent(int days) override
    {
        if (days > 3)
            return (rentalPricePerDay * days) * 0.95;
        else
            return (rentalPricePerDay * days);
    }
    void displayInfo() override
    {
        Vehicle::displayInfo();
        cout << "Helmet included: ";
        if (helmetIncluded)
            cout << "Yes" << endl;
        else
            cout << "No" << endl;
        cout << "Fuel type: " << fuelType << endl;
    }
};
class Truck : public Vehicle
{
protected:
    double cargoCapacity;
    int wheels;

public:
    Truck(double p, double c, int w) : Vehicle(p, "Truck"), cargoCapacity(c), wheels(w) {}
    double rent(int days) override
    {
        if (days > 5)
            return (rentalPricePerDay * days) * 1.2;
        else
            return (rentalPricePerDay * days);
    }
    void displayInfo() override
    {
        Vehicle::displayInfo();
        cout << "Cargo capacity: " << cargoCapacity << endl;
        cout << "Number of wheels: " << wheels << endl;
    }
};
int main()
{
    cout << "Customer 1 (Car Rental):" << endl;
    Car car(10, true, 4);
    car.displayInfo();
    car.Vehicle::rent(10, "Credit Card");
    cout << endl;

    cout << "Customer 2 (Bike Rental):" << endl;
    Bike bike(20, true, "Petrol");
    bike.displayInfo();
    bike.Vehicle::rent(4, "Cash");
    cout << endl;

    cout << (car + bike) << endl;
}
