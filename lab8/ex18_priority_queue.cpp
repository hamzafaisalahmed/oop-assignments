#include <iostream>
#include <queue>
#include <stdexcept>

template <typename T, typename PriorityFunc = std::less<T>>
class PriorityQueue
{
public:
    void insert(const T &element)
    {
        pq.push(element);
    }
    T getHighestPriority()
    {
        if (!pq.empty())
            return pq.top();
        else
            throw std::underflow_error("Queue is empty");
    }

private:
    std::priority_queue<T, std::vector<T>, PriorityFunc> pq;
};
template <typename T>
struct func
{
    bool operator()(const T &a, const T &b)
    {
        return a > b;
    }
};

int main()
{
    PriorityQueue<int, func<int>> PQ;
    PQ.insert(100);
    PQ.insert(20);
    PQ.insert(30);
    std::cout << "smallest value: " << PQ.getHighestPriority()
              << std::endl;
}