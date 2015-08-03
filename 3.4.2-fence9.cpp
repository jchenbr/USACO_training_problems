/*
ID: jchenbr1
LANG: C++11
TASK: fence9
 */
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int main()
{
    ifstream fin("fence9.in");
    ofstream fout("fence9.out");

    double n, m, p;
    while (fin >> n >> m >> p)
    {
        double L = 0, R = p;
        const double eps = 1e-9;
        long long ans = 0;
        for (double h = 1.0; h < m; h += 1.0)
        {
            L = h * n / m;
            R = p - h * (p - n) /m;
            //clog << "L = " << L << "| " << ceil(L) << ", R = " << R << "| " << floor(R) << endl;
            ans += ceil(R - eps) - floor(L + eps) - 1;
        }
        clog << ans << endl;
        fout << ans << endl;
    }

    return 0;
}
