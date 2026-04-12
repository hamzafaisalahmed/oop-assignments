#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
#include <vector>
using namespace std;

struct SensorReading
{
    int sensorId;
    string location;
    string sensorType;
    double value;
};

struct Alert
{
    int priority;
    string message;
    string alertType;
    bool operator<(const Alert &a) const
    {
        return priority < a.priority;
    }
};

class SensorProcessor
{
    priority_queue<Alert> alertQueue;
    unordered_map<int, SensorReading> sensorMap;
    unordered_map<string, vector<SensorReading>> locationMap;

public:
    void addSensorReading(const SensorReading &reading)
    {
        sensorMap[reading.sensorId] = reading;
        locationMap[reading.location].push_back(reading);
    }
    void addAlert(const Alert &alert)
    {
        alertQueue.push(alert);
    }
    void processNextAlert()
    {
        if (alertQueue.empty())
        {
            cout << "No alerts." << endl;
            return;
        }
        Alert alert = alertQueue.top();
        cout << alert.message << endl;
        alertQueue.pop();
    }
    SensorReading *findSensorById(int sensorId)
    {
        auto temp = sensorMap.find(sensorId);
        if (temp != sensorMap.end())
        {
            return &(temp->second);
        }
        return nullptr;
    }
    vector<SensorReading> getSensorsByLocation(const string &location)
    {
        auto temp = locationMap.find(location);
        if (temp == locationMap.end())
        {
            vector<SensorReading> emp;
            return emp;
        }
        return temp->second;
    }
};

int main()
{
    SensorProcessor campusSystem;
    campusSystem.addSensorReading({101, "Library", "Temperature", 22.5});
    campusSystem.addSensorReading({102, "Library", "Humidity", 45.0});
    campusSystem.addSensorReading({201, "Lab A", "Smoke", 0.02});
    cout << "ID Lookup ------------------" << endl;
    SensorReading *s = campusSystem.findSensorById(101);
    if (s)
    {
        cout << "Found Sensor 101: " << s->sensorType << " at " << s->location << endl;
    }
    else
        cout << "Not found" << endl;
    s = campusSystem.findSensorById(111);
    if (s)
    {
        cout << "Found Sensor 111: " << s->sensorType << " at " << s->location << endl;
    }
    else
        cout << "Not found" << endl;

    cout << "\nLocation Query: Library --------------" << endl;
    vector<SensorReading> librarySensors = campusSystem.getSensorsByLocation("Library");
    for (auto &sensor : librarySensors)
    {
        cout << "Sensor ID: " << sensor.sensorId << " (" << sensor.sensorType << ")" << endl;
    }

    vector<SensorReading> unknown = campusSystem.getSensorsByLocation("Unknown");
    if (unknown.empty())
    {
        cout << "No sensors found at Unknown location." << endl;
    }

    cout << "\nProcessing Alerts -----------------" << endl;
    campusSystem.addAlert({5, "issue 1", "Maintenance"});
    campusSystem.addAlert({10, "issue 2", "Emergency"});
    campusSystem.addAlert({1, "issue 3", "System"});

    campusSystem.processNextAlert();
    campusSystem.processNextAlert();
    campusSystem.processNextAlert();
    campusSystem.processNextAlert();
}