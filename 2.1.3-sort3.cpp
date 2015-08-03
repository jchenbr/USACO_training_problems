/*
ID: jchenbr1
LANG: C++11
TASK: sort3
 */

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;


int main()
{
    ifstream fin("sort3.in");
    ofstream fout("sort3.out");

    int n;
    while (fin >> n)
    {
        vector<int> num(n);
        for (auto & item: num) fin >> item;
        vector<int> ord(num);
        sort(begin(ord), end(ord));

        int occ[4][4];
        memset(occ, 0, sizeof(occ));

        for (size_t idx = 0; idx < num.size(); idx++)
            occ[ord[idx]][num[idx]]  += 1;

        int ans = 0;
        for (int i = 1; i <= 3; i++ )
            for (int j = 1; j <= 3; j++)
                if (i != j)
                {
                    int val = min(occ[i][j], occ[j][i]);
                    ans += val;
                    occ[i][j] -= val;
                    occ[j][i] -= val;
                }

        for (int i = 1; i <= 3; i++)
            for (int j = 1; j <= 3; j++)
                for (int k = 1; k <= 3; k++)
                {
                    if (i == j || j == k || k == i) continue;
                    int val = min(occ[i][j], min(occ[j][k], occ[k][i]));
                    ans += val << 1;
                    occ[i][j] -= val;
                    occ[j][k] -= val;
                    occ[k][i] -= val;
                }

        fout << ans << endl;
        clog << ans << endl;
    }

    return 0;
}
