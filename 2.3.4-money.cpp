/*
ID: jchenbr1
LANG: C++11
TASK: money
 */
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main()
{
    ifstream fin("money.in");
    ofstream fout("money.out");

    int n , m;
    while (fin >> m >> n)
    {
        vector<int> cash(m);
        for (auto & one : cash) fin >> one;

        vector<long long> cap(n + 1, 0);
        cap[0] = 1;

        for (auto & c: cash)
            for (int i = c; i <= n; i++)
                cap[i] += cap[i - c];

        for (auto & c: cap) clog << c << " "; clog << endl; 

        clog << cap[n] << endl;
        fout << cap[n] << endl;
    }

    return 0;
}
