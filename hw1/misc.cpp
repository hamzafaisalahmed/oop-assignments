#include <iostream>
#include <cmath>
using namespace std;

class Player
{

    int ID;
    string Name;
    int Level;
    int ArrivalOrder;
    string Player_Type;

public:
    Player(int id, string name, int level, string player_type, int arrival_order)
    {
        ID = id;
        Name = name;
        Level = level;
        Player_Type = player_type;
        ArrivalOrder = arrival_order;
    }

    int getId() const { return ID; }
    string getName() const { return Name; }
    int getLevel() const { return Level; }
    string getType() const { return Player_Type; }
    int getArrivalOrder() const { return ArrivalOrder; }
    void setLevel(int level) { Level = level; }
};

struct Node
{

    Player *player;
    Node *next = nullptr;
};

struct HashNode
{
    int id;
    Player *playerPtr;
    HashNode *next;

    HashNode(int _id, Player *_p, HashNode *_n = nullptr)
        : id(_id), playerPtr(_p), next(_n) {}
};

class IDHashTable
{
private:
    static const int TABLE_SIZE = 150001; // Large prime for O(1)
    HashNode *table[TABLE_SIZE];

    int hashFunction(int id)
    {
        return (id < 0 ? -id : id) % TABLE_SIZE;
    }

public:
    IDHashTable()
    {
        for (int i = 0; i < TABLE_SIZE; i++)
            table[i] = nullptr;
    }

    // Insert for REGISTER
    bool insert(int id, Player *p)
    {
        int index = hashFunction(id);
        HashNode *curr = table[index];
        while (curr)
        {
            if (curr->id == id)
                return false; // Duplicate found
            curr = curr->next;
        }
        table[index] = new HashNode(id, p, table[index]);
        return true;
    }

    // Lookup for BOOST/WITHDRAW
    Player *getPlayer(int id)
    {
        int index = hashFunction(id);
        HashNode *curr = table[index];
        while (curr)
        {
            if (curr->id == id)
                return curr->playerPtr;
            curr = curr->next;
        }
        return nullptr;
    }

    // The Withdraw/Remove Logic
    void remove(int id)
    {
        int index = hashFunction(id);
        HashNode *curr = table[index];
        HashNode *prev = nullptr;

        while (curr)
        {
            if (curr->id == id)
            {
                if (prev)
                    prev->next = curr->next; // Bypass the node
                else
                    table[index] = curr->next; // It was the head of the chain
                delete curr;
                return;
            }
            prev = curr;
            curr = curr->next;
        }
    }
};

// 3. Custom Undo System
struct Action
{
    string type; // "REGISTER", "PLAY", "BOOST", "WITHDRAW"
    Player *player;
    int value; // Used for old level in BOOST
    Action *next;
};

class ChampionshipManager
{
private:
    IDHashTable registry;
    Node *vipHead;    // Priority Queue for VIPs
    Node *normalHead; // FIFO Queue for Normal
    Node *normalTail;
    Action *undoTop;    // Undo Stack
    int arrivalCounter; // Global counter

    int vipCount, normalCount;

public:
    ChampionshipManager()
    {

        vipHead = nullptr;
        normalHead = nullptr;
        normalTail = nullptr;
        undoTop = nullptr;

        arrivalCounter = 0;
        vipCount = 0;
        normalCount = 0;
    }

    // Priority insertion for VIPs
    void insertVIP(Player *p)
    {
        if (!vipHead || p->getLevel() > vipHead->player->getLevel() ||
            (p->getLevel() == vipHead->player->getLevel() && p->getArrivalOrder() < vipHead->player->getArrivalOrder()))
        {

            Node *new_node = new Node;
            new_node->player = p;
            new_node->next = vipHead;
            vipHead = new_node;
        }
        else
        {

            Node *curr = vipHead;
            while (curr->next && (curr->next->player->getLevel() > p->getLevel() ||
                                  (curr->next->player->getLevel() == p->getLevel() && curr->next->player->getArrivalOrder() < p->getArrivalOrder())))
            {
                curr = curr->next;
            }
            Node *new_node = new Node;
            new_node->player = p;
            new_node->next = curr->next;
            curr->next = new_node;
        }

        vipCount++;
    }

    void Register(int id, string name, int level, string type)
    {

        // Successful registration
        Player *p = new Player(id, name, level, type, arrivalCounter);
        if (!registry.insert(id, p))
        {
            delete p;
            return;
        }

        arrivalCounter++;

        if (type == "VIP")
        {
            insertVIP(p);
        }
        else
        {
            Node *new_node = new Node;
            new_node->player = p;
            if (!normalTail)
                normalHead = normalTail = new_node;
            else
            {
                normalTail->next = new_node;
                normalTail = new_node;
            }
            normalCount++;
        }

        Action *new_action = new Action; // Record for undo
        new_action->type = "REGISTER";
        new_action->player = p;
        new_action->value = level;
        new_action->next = undoTop;
        undoTop = new_action;
    }

    void play()
    {

        Player *p = nullptr;

        if (vipHead)
        {
            p = vipHead->player;
            Node *temp = vipHead;
            vipHead = vipHead->next;
            delete temp;
            vipCount--;
        }
        else if (normalHead)
        {
            p = normalHead->player;
            Node *temp = normalHead;
            normalHead = normalHead->next;
            if (!normalHead)
                normalTail = nullptr;
            delete temp;
            normalCount--;
        }

        if (p)
        {
            cout << p->getId() << " " << p->getName() << endl;

            Action *new_action = new Action; // Record for undo
            new_action->type = "PLAY";
            new_action->player = p;
            new_action->value = 0;
            new_action->next = undoTop;
            undoTop = new_action;
        }
        else
        {
            cout << "NO PLAYERS" << endl;
        }
    }

    void status()
    {
        cout << "VIP Count: " << vipCount << " NORMAL Count: " << normalCount << endl;
    }

    // Note: BOOST and WITHDRAW require ID lookup logic

    void withdraw(int id, bool recordUndo = true)
    {
        // 1. Check if the player even exists
        Player *p = registry.getPlayer(id);
        if (!p)
            return; // Ignore if does not exist

        // 2. Remove from the Central Registry (ID becomes available)
        registry.remove(id);

        // 3. Remove from the specific Queue
        if (p->getType() == "VIP")
        {
            removeFromList(vipHead, id);
            vipCount--;
        }
        else
        {
            removeFromList(normalHead, id);

            if (normalHead == nullptr)
                normalTail = nullptr;
            else
            {
                Node *tail = normalHead;
                while (tail->next)
                    tail = tail->next;
                normalTail = tail;
            }
            normalCount--;
        }

        // // 4. Record for UNDO
        // undoTop = new Action{"WITHDRAW", p, 0, undoTop};

        if (recordUndo)
        {
            // Only add to stack if this wasn't called by an UNDO command
            Action *new_action = new Action{"WITHDRAW", p, 0, undoTop};
            undoTop = new_action;
        }
    }

    // Helper to remove a specific node from a manual linked list
    void removeFromList(Node *&head, int id)
    {
        Node *curr = head;
        Node *prev = nullptr;

        while (curr)
        {
            if (curr->player->getId() == id)
            {
                if (prev)
                    prev->next = curr->next;
                else
                    head = curr->next;
                delete curr;
                return;
            }
            prev = curr;
            curr = curr->next;
        }
    }

    void boost(int id, int x)
    {
        // 1. Use the Hash Table for O(1) lookup
        Player *p = registry.getPlayer(id);

        // 2. Ignore if player doesn't exist or is NORMAL
        if (!p || p->getType() == "NORMAL")
            return;

        // 3. Record state for UNDO (Store the old level)
        Action *new_action = new Action;
        new_action->type = "BOOST";
        new_action->player = p;
        new_action->value = x; // Store the increase amount to reverse it later
        new_action->next = undoTop;
        undoTop = new_action;

        // 4. Update Level
        // Note: Re-sorting is required. The easiest way is to withdraw and re-insert.
        removeFromList(vipHead, id);
        p->setLevel(p->getLevel() + x);
        insertVIP(p);
    }

    void undo()
    {
        if (!undoTop)
            return; // No operations to undo

        Action *act = undoTop;
        undoTop = undoTop->next; // Pop the stack

        if (act->type == "REGISTER")
        {
            // Reverse Register: Simply withdraw the player
            // Note: You should call a version of withdraw that doesn't add to UNDO stack
            withdraw(act->player->getId(), false);
        }
        else if (act->type == "PLAY")
        {
            // Reverse Play: Put the player back in their queue
            if (act->player->getType() == "VIP")
            {
                insertVIP(act->player);
            }
            else
            {
                // Re-inserting into FIFO for Normal players
                // For a perfect undo, they should go back to the front.
                Node *newNode = new Node;
                newNode->player = act->player;
                newNode->next = normalHead;
                normalHead = newNode;
                if (!normalTail)
                    normalTail = newNode;
                normalCount++;
            }
        }
        else if (act->type == "BOOST")
        {
            // Reverse Boost: Decrease the level by the boosted amount
            removeFromList(vipHead, act->player->getId());
            act->player->setLevel(act->player->getLevel() - act->value);
            insertVIP(act->player);
        }
        else if (act->type == "WITHDRAW")
        {
            // Reverse Withdraw: Re-register the player =
            if (act->player->getType() == "VIP")
            {
                insertVIP(act->player);
            }
            else
            {
                // Add back to the Normal queue
                Node *newNode = new Node;
                newNode->player = act->player;
                newNode->next = nullptr;
                if (!normalTail)
                    normalHead = normalTail = newNode;
                else
                {
                    normalTail->next = newNode;
                    normalTail = newNode;
                }
                normalCount++;
            }
            registry.insert(act->player->getId(), act->player);
        }

        delete act; // Clean up the action node
    }
};

int main()
{

    ChampionshipManager manager;
    int Q;

    // Read the number of operations
    if (!(cin >> Q))
        return 0;

    for (int i = 0; i < Q; i++)
    {
        string command;
        cin >> command;

        if (command == "REGISTER")
        {
            int id, level;
            string name, type;
            cin >> id >> name >> level >> type;
            manager.Register(id, name, level, type);
        }
        else if (command == "PLAY")
        {
            manager.play();
        }
        else if (command == "STATUS")
        {
            manager.status();
        }
        else if (command == "WITHDRAW")
        {
            int id;
            cin >> id;
            manager.withdraw(id);
        }
        else if (command == "BOOST")
        {
            int id, x;
            cin >> id >> x;
            manager.boost(id, x);
        }
        else if (command == "UNDO")
        {
            manager.undo();
        }
    }
}