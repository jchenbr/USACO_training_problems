/*
ID: jchenbr1
LANG: C++11
TASK: stamps
 */
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;

int main()
{
    ifstream fin("stamps.in");
    ofstream fout("stamps.out");

    int n, m;
    while (fin >> m >> n)
    {
        vector<int> stamps(n);
        for (auto & s: stamps) fin >> s;
        sort(begin(stamps), end(stamps));

        vector<int> opt(stamps.back() * m + 1, m + 1);
        opt[0] = 0;
        int ans = 0;

        for (int i = 1; i < (int)opt.size(); i++)
        {
            for (int j = 0; j < n && i >= stamps[j]; j++)
               opt[i] = min(opt[i], opt[i - stamps[j]] + 1);

            if (opt[i] <= m)
                ans = i;
            else 
                break;
        }

        fout << ans << endl;
        clog << ans << endl;
    }

    return 0;
}
