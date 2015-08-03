/*
ID: jchenbr1
LANG: C++11
TASK: milk
 */
#include <iostream>
#include <fstream>
#include <set>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char ** argv)
{
    ifstream fin("milk.in");
    ofstream fout("milk.out");

    int n, m;
    while (fin >> n >> m)
    {
        vector<pair<int, int> > provider(m);
        for (auto & john: provider)
        {
            fin >> john.first >> john.second;
        }

        sort(begin(provider), end(provider));

        int pay = 0;
        for (auto & john: provider)
        {
            pay += john.first * min(john.second, n);
            n -= min(john.second, n);
            if (n == 0) break;
        }

        fout << pay << endl;
        clog << pay << endl;
    }

    return 0;
}
