#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <iomanip>
#include <numeric>
using namespace std;

struct Order
{
    int id;
    string customer;
    double amount;
    bool isPaid;
};

int main()
{
    vector<Order> orders = {
        {1, "Alice", 100.0, true},
        {2, "Bob", 150.0, false},
        {3, "Charlie", 200.0, true},
        {4, "David", 250.0, false},
        {5, "Eve", 300.0, true},
        {6, "Frank", 350.0, false},
        {7, "Grace", 400.0, true},
        {8, "Heidi", 450.0, false}};

    // filter
    function<vector<Order>(const vector<Order> &)> filter = [](const vector<Order> &orders)
    {
        vector<Order> arr;
        copy_if(orders.begin(), orders.end(), back_inserter(arr), [](const Order &o)
                { return (o.amount > 100) && o.isPaid; });
        return arr;
    };

    // map
    function<vector<double>(const vector<Order> &)> map = [](const vector<Order> &arr)
    {
        vector<double> discount(arr.size());
        transform(arr.begin(), arr.end(), discount.begin(), [](const Order &o)
                  { return o.amount * 0.9; });
        return discount;
    };

    // reduce
    function<double(const vector<double> &)> Reduce = [](const vector<double> &discount)
    {
        double sum = accumulate(discount.begin(), discount.end(), 0.0);
        return sum;
    };

    // pipeline
    auto qualifyingOrders = filter(orders);
    auto discountedPrices = map(qualifyingOrders);
    double totalRevenue = Reduce(discountedPrices);

    cout << fixed << setprecision(2);
    cout << "Qualifying Orders: " << qualifyingOrders.size() << endl;
    cout << "Total discounted revenue: $" << totalRevenue << endl;
}