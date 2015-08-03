/*
ID: jchenbr1
LANG: C++11
TASK: inflate
 */
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main()
{
    ifstream fin("inflate.in");
    ofstream fout("inflate.out");

    int n, m;
    while (fin >> m >> n)
    {
        vector<int> opt(m + 1, 0);
        while (n--)
        {
            int val, cost;
            fin >> val >> cost;
            for (int i = cost; i <= m; i++)
                opt[i] = max(opt[i - cost] + val, opt[i]);
        }
        fout << opt[m] << endl;
        clog << opt[m] << endl;
    }

    return 0;
}
