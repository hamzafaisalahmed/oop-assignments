#include <iostream>

using namespace std;

class Node
{
public:
    char data;
    Node *next;
    Node(int data)
    {
        this->data = data;
        next = nullptr;
    }
};

class Queue
{
    Node *front;
    Node *rear;
    int size;

public:
    Queue()
    {
        front = nullptr;
        rear = nullptr;
        size = 0;
    }
    void enqueue(char d)
    {
        Node *temp = new Node(d);
        if (size == 0)
        {
            size++;
            front = temp;
            rear = temp;
            return;
        }
        else
        {
            size++;
            rear->next = temp;
            rear = temp;
            return;
        }
    }
    char dequeue()
    {
        if (size == 0)
        {
            throw underflow_error("Queue size is already 0");
        }
        else if (size == 1)
        {
            size--;
            front = nullptr;
            Node *temp = rear;
            rear = nullptr;
            char data = temp->data;
            delete temp;
            return data;
        }
        else
        {
            size--;
            Node *temp = front;
            front = front->next;
            char data = temp->data;
            delete temp;
            return data;
        }
    }
    void removeArr(char *arr, int s)
    {

        Node *prev = nullptr;
        Node *curr = front;

        while (curr != nullptr)
        {
            bool flag = false;
            for (int i = 0; i < s; i++)
            {
                char temp = arr[i];
                if (curr->data == temp)
                {
                    flag = true;
                    break;
                }
            }
            if (!flag)
            {
                prev = curr;
                curr = curr->next;
            }

            else if (curr == front && size > 0)
            {
                front = front->next;
                size--;
                delete curr;
                curr = front;
                if (size == 0)
                    rear = nullptr;
            }
            else if (curr == rear)
            {
                rear = prev;
                rear->next = nullptr;
                size--;
                delete curr;
                curr = rear;
                if (size == 0)
                    front = nullptr;
            }
            else
            {
                prev->next = curr->next;
                size--;
                delete curr;
                curr = prev->next;
            }
        }
    }
    void Display()
    {
        Node *curr = front;
        for (int i = 0; i < size; i++)
        {
            cout << curr->data << " ";
            curr = curr->next;
        }
        cout << endl;
    }
};

int main()
{
    Queue q;

    char chars[] = {'A', 'C', 'E'};

    cout << "Input length of list: ";
    int len;
    cin >> len;
    cout << "Input list: " << endl;

    char c;
    for (int i = 0; i < len; i++)
    {
        cin >> c;
        q.enqueue(c);
    }
    q.Display();

    q.removeArr(chars, 3);

    q.Display();

    return 0;
}