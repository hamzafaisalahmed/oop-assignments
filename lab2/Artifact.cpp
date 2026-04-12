#include <iostream>
#include <string>

using namespace std;

class Artifact
{
    string name;
    string registrationID;
    string discoverer;
    string origin;

public:
    Artifact(string n, string ID, string dis, string org)
    {
        this->name = n;
        this->registrationID = ID;
        this->discoverer = dis;
        this->origin = org;
    }
    string getName()
    {
        return this->name;
    }
    string getRegistrationID()
    {
        return this->registrationID;
    }
    string getDiscoverer()
    {
        return this->discoverer;
    }
    string getOrigin()
    {
        return this->origin;
    }
    string getArtifactInfo()
    {
        string info;
        info += "Name: " + this->name + "\n";
        info += "Registration ID: " + this->registrationID + "\n";
        info += "Discoverer: " + this->discoverer + "\n";
        info += "Origin: " + this->origin + "\n";
        return info;
    }
};

int main()
{
    Artifact arr[5] = {
        Artifact("pot", "a01", "name1", "indus valley"),
        Artifact("Sword", "b22", "unnamed person2", "England"),
        Artifact("Painting", "A03", "random explorer", "Italy"),
        Artifact("Egyptian artifact", "e4", "Dr. doctor", "Egypt"),
        Artifact("statue", "a2", "mr statue", "sukkur")};
    for (int i = 0; i < 5; i++)
    {
        cout << arr[i].getArtifactInfo() << endl;
    }
}