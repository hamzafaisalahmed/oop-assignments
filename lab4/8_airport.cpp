#include <iostream>
#include <vector>
using namespace std;
class plane
{
public:
    string flightNo;
    string operation;
    int severity;
    string time;
    plane *next;
    plane(string f, string o, int s, string t)
    {
        flightNo = f;
        operation = o;
        severity = s;
        time = t;
        next = nullptr;
    }
};

class takeoff
{
    plane *top;
    int size;

public:
    takeoff()
    {
        top = nullptr;
        size = 0;
    }
    void addPlane(plane *p)
    {
        if (size == 0)
        {
            top = p;
            size++;
            return;
        }
        p->next = top;
        top = p;
        size++;
        return;
    }
    bool takeoffPlane()
    {
        if (size == 0)
            return false;
        size--;
        top = top->next;
        return true;
    }
    void Display()
    {
        plane *curr = top;
        while (curr != nullptr)
        {
            cout << curr->flightNo << " " << curr->time << endl;
            curr = curr->next;
        }
    }
    plane peek()
    {
        if (top != nullptr)
        {
            return *top;
        }
        throw underflow_error("No planes to takeoff");
    }
    int getSize()
    {
        return size;
    }
};

class landing
{
    plane *front;
    int size;

public:
    landing()
    {
        front = nullptr;
        size = 0;
    }
    void addPlane(plane *p)
    {
        if (size == 0)
        {
            front = p;
            size++;
            return;
        }
        plane *curr = front;
        plane *prev = nullptr;
        while (curr != nullptr && (curr->severity > p->severity || (curr->severity == p->severity && curr->time < p->time)))
        {
            prev = curr;
            curr = curr->next;
        }
        if (curr == front)
        {
            p->next = front;
            front = p;
            size++;
            return;
        }
        if (curr == nullptr)
        {
            prev->next = p;
            size++;
            return;
        }
        prev->next = p;
        size++;
        p->next = curr;
        return;
    }
    int getSize()
    {
        return size;
    }
    void Display()
    {
        plane *curr = front;
        while (curr != nullptr)
        {
            cout << curr->flightNo << " " << curr->severity << " " << curr->time << endl;
            curr = curr->next;
        }
    }
    void land()
    {
        if (size == 0)
            return;
        size--;
        front = front->next;
    }
    plane peek()
    {
        if (front != nullptr)
        {
            return *front;
        }
        throw underflow_error("No planes to land");
    }
};

void Tower(takeoff &t, landing &l)
{
    if (t.getSize() == 0 && l.getSize() == 0)
    {
        cout << "No traffic" << endl;
        return;
    }
    else if (l.getSize() != 0)
    {
        plane p = l.peek();
        cout << "Plane " << p.flightNo << " landing at " << p.time << " with severity " << p.severity << endl;
        l.land();
        cout << "__________________________" << endl;
        l.Display();
        cout << "__________________________" << endl;
    }
    else
    {
        plane p = t.peek();
        cout << "Plane " << p.flightNo << " taking off at " << p.time << endl;
        t.takeoffPlane();
        cout << "__________________________" << endl;
        t.Display();
        cout << "__________________________" << endl;
    }
    Tower(t, l);
}

void addToList(plane &p, takeoff &t, landing &l)
{
    if (p.operation == "takeoff")
        t.addPlane(&p);
    else
        l.addPlane(&p);
}

int main()
{
    vector<plane> arr =
        {
            plane("PK-101", "takeoff", 5, "10:00"),
            plane("PK-102", "landing", 7, "10:05"),
            plane("PK-103", "landing", 7, "10:03"),
            plane("PK-104", "takeoff", 3, "10:10"),
            plane("PK-105", "landing", 10, "10:01"),
        };
    takeoff t;
    landing l;

    for (int i = 0; i < arr.size(); i++)
    {
        addToList(arr[i], t, l);
    }
    cout << "Takeoff queue size: " << t.getSize() << endl;
    cout << "Landing queue size: " << l.getSize() << endl;
    Tower(t, l);
}