#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Device
{
    static int totalDevices;
    const int serialNumber = totalDevices++;

public:
    int displayTotalDevices()
    {
        return totalDevices;
    }
    int getSerialNumber()
    {
        return serialNumber;
    }
    void setSerialNumber(int sn)
    {
        // serialNumber = sn; // This line would cause a compilation error since serialNumber is const
    }
};

int Device::totalDevices = 0;

int main()
{
    Device d1;
    Device d2;
    Device d3;
    cout << "Total Devices: " << d3.displayTotalDevices() << endl;
    cout << "Serial Number of d1: " << d1.getSerialNumber() << endl;
    cout << "Serial Number of d2: " << d2.getSerialNumber() << endl;
    cout << "Serial Number of d3: " << d3.getSerialNumber() << endl;
    return 0;
}