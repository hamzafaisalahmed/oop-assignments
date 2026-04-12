#include <iostream>
#include <numeric>
#include <vector>
#include <iomanip>
using namespace std;

int main()
{
    vector<double> data = {4, 8, 15, 16, 23, 42, 7, 3, 19, 11};
    double sum = accumulate(data.begin(), data.end(), 0.0);
    double mean = sum / data.size();
    double min = accumulate(data.begin(), data.end(), data[0], [](double min, double v)
                            {if (v<min) min = v; return min; });
    double max = accumulate(data.begin(), data.end(), data[0], [](double max, double v)
                            {if (v>max) max = v; return max; });
    double ssq = accumulate(data.begin(), data.end(), 0.0, [](double acc, double v)
                            { return acc + (v * v); });
    double var = (ssq / data.size()) - (mean * mean);
    cout << fixed << setprecision(2);
    cout << "Sum: " << sum << " Mean: " << mean << " Min: " << min << " Max: " << max << " SSQ: " << ssq << " Variance: " << var << endl;
    double Rsum = reduce(data.begin(), data.end(), 0.0);
    double Rmean = Rsum / data.size();
    cout << "Reduced sum: " << Rsum << " Reduced mean: " << Rmean;
}