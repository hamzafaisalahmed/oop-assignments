#include <iostream>
#include <vector>
using namespace std;

class Stock
{
public:
    int timestamp;
    int price;
    Stock()
    {
        timestamp = 0;
        price = 0;
    }
};
class StockPrice
{
    vector<Stock> stocks;

public:
    StockPrice()
    {
        stocks = vector<Stock>();
    }
    void update(int t, int p)
    {
        for (int i = 0; i < stocks.size(); i++)
        {
            if (stocks[i].timestamp == t)
            {
                stocks[i].price = p;
                return;
            }
        }
        Stock s;
        s.timestamp = t;
        s.price = p;
        stocks.push_back(s);
    }
    int current()
    {
        int max = 0;
        int maxI = 0;
        for (int i = 0; i < stocks.size(); i++)
        {
            if (stocks[i].timestamp > max)
            {
                max = stocks[i].timestamp;
                maxI = i;
            }
        }
        return stocks[maxI].price;
    }
    int maximum()
    {
        if (stocks.size() == 0)
            return -1;
        int max = stocks[0].price;
        for (int i = 0; i < stocks.size(); i++)
        {
            if (stocks[i].price > max)
            {
                max = stocks[i].price;
            }
        }
        return max;
    }
    int minimum()
    {
        if (stocks.size() == 0)
            return -1;
        int min = stocks[0].price;
        for (int i = 0; i < stocks.size(); i++)
        {
            if (stocks[i].price < min)
            {
                min = stocks[i].price;
            }
        }
        return min;
    }
};

int main()
{
    StockPrice sp;
    sp.update(1, 10);
    sp.update(2, 5);
    sp.update(1, 3);
    sp.update(4, 8);
    sp.update(3, 12);
    cout << sp.current() << endl;
    cout << sp.maximum() << endl;
    cout << sp.minimum() << endl;
}
