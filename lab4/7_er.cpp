#include <iostream>
#include <string>
using namespace std;
class Node
{
public:
    string name;
    string arrivalTime;
    int severity;
    Node *next;
    Node(string n, string t, int s)
    {
        name = n;
        arrivalTime = t;
        severity = s;
        next = nullptr;
    }
};

class Patient
{
    Node *front;
    int size;

public:
    Patient()
    {
        front = nullptr;
        size = 0;
    }
    void addPatient(string n, string t, int s)
    {
        Node *temp = new Node(n, t, s);
        if (size == 0)
        {
            front = temp;
            size++;
            return;
        }
        if (size == 1)
        {
            if (temp->severity > front->severity)
            {
                temp->next = front;
                front = temp;
                size++;
                return;
            }
            else
            {
                if (temp->arrivalTime < front->arrivalTime)
                {
                    temp->next = front;
                    front = temp;
                    size++;
                    return;
                }
            }
            front->next = temp;
            size++;
            return;
        }
        Node *curr = front;
        Node *prev = nullptr;
        while (curr != nullptr && (curr->severity > temp->severity || (curr->severity == temp->severity && curr->arrivalTime < temp->arrivalTime)))
        {
            prev = curr;
            curr = curr->next;
        }
        if (curr == nullptr)
        {
            prev->next = temp;
            size++;
            return;
        }
        else if (curr == front)
        {
            temp->next = front;
            front = temp;
            size++;
            return;
        }
        else
        {
            prev->next = temp;
            temp->next = curr;
            size++;
            return;
        }
    }
    void treatPatient()
    {
        if (size == 0)
            throw underflow_error("No patients to treat");
        else
        {
            size--;
            Node *temp = front;
            front = front->next;
            cout << "Treating: " << temp->name << endl;
            delete temp;
            return;
        }
    }
    void peek()
    {
        if (size == 0)
            throw underflow_error("No patients to treat");
        else
        {
            cout << "Next patient: " << front->name << endl;
            return;
        }
    }
};

int main()
{
    Patient p;
    p.addPatient("one", "10:00", 3);
    p.addPatient("two", "10:05", 7);
    p.addPatient("three", "10:10", 10);
    p.addPatient("four", "10:15", 7);
    p.addPatient("five", "10:20", 7);
    p.peek();
    p.treatPatient();
    p.treatPatient();
    p.treatPatient();
}