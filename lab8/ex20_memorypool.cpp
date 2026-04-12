#include <iostream>
#include <chrono>
using namespace std;

class MemoryPool
{
    char *pool;
    size_t total;
    size_t used;

public:
    MemoryPool(size_t totalSize) : total(totalSize), used(0) { pool = new char[total]; }
    void *allocate(size_t objSize)
    {
        if (used + objSize > total)
            throw overflow_error("Max size reached");
        void *add = pool + used;
        used += objSize;
        return add;
    }

    void reset()
    {
        used = 0;
    }
    ~MemoryPool()
    {
        delete[] pool;
    }
};

int main()
{
    const int iterations = 1000000;

    auto start1 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < iterations; ++i)
    {
        int *ptr = new int[100];
        delete[] ptr;
    }
    auto end1 = chrono::high_resolution_clock::now();
    chrono::duration<double> delta = end1 - start1;
    cout << "Standard time: " << delta.count() << endl;
    try
    {
        MemoryPool myPool(iterations * sizeof(int[100]));
        auto start2 = chrono::high_resolution_clock::now();
        for (int i = 0; i < iterations; i++)
        {
            void *mem = myPool.allocate(sizeof(int[100]));
            int *ptr = (int *)mem;
        }
        auto end2 = chrono::high_resolution_clock::now();
        chrono::duration<double> delta2 = end2 - start2;
        cout << "Memory Pool time: " << delta2.count() << endl;
    }
    catch (const overflow_error &e)
    {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
    return 0;
}