#include <iostream>
#include <string>
#include <cstring>
using namespace std;

class User
{
    int age;
    string name;
    char *profileBio;
    int *sessionID;

public:
    User(int age, string name, char *profileBio, int sessionID)
    {
        this->age = age;
        this->name = name;

        this->profileBio = new char[strlen(profileBio) + 1];
        strcpy(this->profileBio, profileBio);
        this->sessionID = new int(sessionID);
    }
    User(const User &obj)
    {
        this->name = obj.name;
        this->age = obj.age;

        this->profileBio = new char[strlen(obj.profileBio) + 1];
        strcpy(this->profileBio, obj.profileBio);
        this->sessionID = obj.sessionID;
    }
    void Display()
    {
        if (this->sessionID != nullptr)
        {
            cout << "Name: " << this->name << "\nAge: " << this->age;
            if (strlen(this->profileBio) > 0)
                cout << "\nProfile Bio: " << this->profileBio;
            else
                cout << "\nProfile Bio: NOT FOUND";
            if (this->sessionID != nullptr)
                cout << "\nSession ID: " << *(this->sessionID) << endl;
            else
                cout << "\nSession ID: NOT FOUND" << endl;
        }
        else
            cout << "No session ID found for user " << this->name << endl;
    }

    void setProfileBio(char *profileBio)
    {
        delete[] this->profileBio;
        this->profileBio = new char[strlen(profileBio) + 1];
        strcpy(this->profileBio, profileBio);
    }
    void setSessionID(int sessionID)
    {
        *(this->sessionID) = sessionID;
    }
    void setName(string name)
    {
        this->name = name;
    }
    void setAge(int age)
    {
        this->age = age;
    }
    int getSessionID()
    {
        return *(this->sessionID);
    }

    ~User()
    {
        delete[] profileBio;
        cout << "User " << this->name << " was deleted..." << endl;
    }
};

int main()
{

    int sessionID = 12;
    User obj(22, "Ali", "BS CS student", sessionID);
    User obj2(obj);
    obj.Display();
    cout << endl;
    obj2.Display();
    cout << endl;

    cout << "Changing profile bio..." << endl;
    obj.setProfileBio("BS math student");
    obj.Display();
    cout << endl;
    obj2.Display();
    cout << endl;

    cout << "Changing session ID..." << endl;
    sessionID = 19;
    obj.setSessionID(sessionID);
    obj.Display();
    cout << endl;
    obj2.Display();
    cout << endl;
}

// different users can have same session ID but each user will have a unique profile bio.
// to make sure multiple users have same sessionID, we must use shallow copy,
// and to ensure that each users profileBio is not interdependent, we use deep copy.