#include <iostream>

using namespace std;

template <typename T>
class Node
{
public:
    T data;
    Node *next;
    Node(T d) : data(d), next(nullptr) {}
};
template <typename T>
class LinkedList
{
    Node<T> *head;
    Node<T> *tail;
    int size;

public:
    LinkedList() : head(nullptr), tail(nullptr), size(0) {}
    void insert(T data)
    {
        Node<T> *node = new Node(data);
        if (!head)
            head = tail = node;
        else
        {
            tail->next = node;
            tail = node;
        }
        size++;
    }
    T Delete(T data)
    {
        if (size == 0)
            throw underflow_error("List already empty");
        Node<T> *curr = head;
        Node<T> *prev = nullptr;
        while (curr != nullptr)
        {
            if (curr->data == data)
                break;
            prev = curr;
            curr = curr->next;
        }
        if (curr && curr->data == data)
        {
            if (prev == nullptr)
                head = curr->next;
            else if (curr == tail)
            {
                tail = prev;
                tail->next = nullptr;
            }
            else if (prev == nullptr && curr == tail)
                head = tail = nullptr;
            else
                prev->next = curr->next;
            T data = curr->data;
            delete curr;
            size--;
            return data;
        }
        throw invalid_argument("Data not found in list");
    }
    void traversal()
    {
        Node<T> *curr = head;
        while (curr != nullptr)
        {
            cout << curr->data << " ";
            curr = curr->next;
        }
        cout << endl;
    }

    ~LinkedList()
    {
        Node<T> *curr = head;
        while (curr != nullptr)
        {
            Node<T> *temp = curr;
            curr = curr->next;
            delete temp;
        }
    }
};

int main()
{
    try
    {
        LinkedList<int> list;
        list.insert(1);
        list.insert(2);
        list.insert(3);
        list.traversal();
        cout << "Deleted: " << list.Delete(2) << endl;
        list.traversal();
    }
    catch (const exception &e)
    {
        cerr << "Error: " << e.what() << endl;
    }
}