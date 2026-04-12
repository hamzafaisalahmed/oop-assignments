#include <iostream>
#include <string>

using namespace std;

class Vehicle
{
protected:
    string registrationNo;
    string brand;
    double dailyRate;

public:
    Vehicle(string r, string b, double dr) : registrationNo(r), brand(b), dailyRate(dr) {}
    void displayVehicle()
    {
        cout << "Registration No: " << registrationNo << endl;
        cout << "Brand: " << brand << endl;
        cout << "Daily Rate: $" << dailyRate << endl;
    }
};

class Car : public Vehicle
{
private:
    int numDoors;

public:
    Car(string r, string b, double dr, int nd) : Vehicle(r, b, dr), numDoors(nd) {}
    void displayVehicle()
    {
        Vehicle::displayVehicle();
        cout << "Number of Doors: " << numDoors << endl;
    }
};

class ElectricCar : public Car
{
private:
    double batteryCapacity;

public:
    ElectricCar(string r, string b, double dr, int nd, double bc) : Car(r, b, dr, nd), batteryCapacity(bc) {}
    void displayVehicle()
    {
        Car::displayVehicle();
        cout << "Battery Capacity: " << batteryCapacity << "kWh" << endl;
    }
    double calculateRentalCost(int days)
    {
        return dailyRate * days * 0.85;
    }
};

class Truck : private Vehicle
{
private:
    double payloadCapacity;

public:
    Truck(string r, string b, double dr, double pc) : Vehicle(r, b, dr), payloadCapacity(pc) {}
    void displayTruck()
    {
        Vehicle::displayVehicle();
        cout << "Payload capacity: " << payloadCapacity << " tonnes " << endl;
    }
    // registrationNo is already accessible
};

int main()
{
    Car myCar("ABC-123", "Toyota", 50.0, 4);
    ElectricCar myEV("EV-999", "Tesla", 80.0, 4, 75.0);
    Truck myTruck("TRK-777", "Volvo", 120.0, 15.0);

    cout << "--- Car Info ---" << endl;
    myCar.displayVehicle();

    cout << "\n--- Electric Car Info ---" << endl;
    myEV.displayVehicle();
    cout << "7-Day Rental Cost (Green Discount): $" << myEV.calculateRentalCost(7) << endl;

    cout << "\n--- Truck Info ---" << endl;
    myTruck.displayTruck();
}