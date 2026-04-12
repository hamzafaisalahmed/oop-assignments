#include <iostream>

using namespace std;

struct Node
{
    int data = 0;
    Node *next = nullptr;
};

Node *reverse(Node *head)
{
    if (head == nullptr || head->next == nullptr)
        return head;
    Node *prev = nullptr;
    Node *curr = head;
    Node *next = nullptr;
    while (curr != nullptr)
    {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    return prev;
}

int main()
{

    Node *head = new Node();
    head->data = 1;
    Node *temp = head;
    for (int i = 2; i <= 5; i++)
    {
        temp->next = new Node();
        temp = temp->next;
        temp->data = i;
    }
    cout << "Original list: ";
    temp = head;
    while (temp != nullptr)
    {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
    head = reverse(head);
    cout << "Reversed list: ";
    temp = head;
    while (temp != nullptr)
    {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}