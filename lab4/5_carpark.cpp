#include <iostream>

using namespace std;

class CircularDriveThru
{
    int front;
    int rear;
    int size;
    int len;
    int *lane;

public:
    CircularDriveThru(int k)
    {
        lane = new int[k]{};
        len = k;
        front = 0;
        rear = 0;
        size = 0;
    }
    bool parkCar(int carNo)
    {
        if (size + 1 <= len)
        {
            lane[rear] = carNo;
            size++;

            rear = (rear + 1) % len;
            return true;
        }
        else
            return false;
    }
    bool carLeaves()
    {
        if (size == 0)
            return false;
        else
        {
            lane[front] = 0;
            size--;

            front = (front + 1) % len;
            return true;
        }
    }
    int frontCar()
    {
        if (size == 0)
            return -1;
        else
            return lane[front];
    }
    int lastCar()
    {
        if (size == 0)
            return -1;
        else
            return lane[rear];
    }
    bool isEmpty()
    {
        return size == 0;
    }
    bool isFull()
    {
        return size == len;
    }
    void Display()
    {
        for (int i = 0; i < len; i++)
        {
            cout << lane[i] << " ";
        }
        cout << endl;
    }
    ~CircularDriveThru()
    {
        delete[] lane;
    }
};

int main()
{
    CircularDriveThru *obj = new CircularDriveThru(3);
    obj->parkCar(101);
    obj->parkCar(102);
    obj->parkCar(103);
    obj->Display();
    cout << obj->parkCar(104) << endl;

    obj->carLeaves();

    obj->parkCar(104);
    obj->Display();
}