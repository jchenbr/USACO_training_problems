/*
ID: jchenbr1
LANG: C++11
TASK: bigbrn
 */
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    ifstream fin("bigbrn.in");
    ofstream fout("bigbrn.out");

    int n, m;
    while (fin >> n >> m)
    {
        vector<vector<bool> > a(n + 1, vector<bool>(n + 1, false));
        vector<vector<int> > f(n + 1, vector<int>(n + 1, 0));
        vector<vector<int> > u(n + 1, vector<int>(n + 1, 0));
        vector<vector<int> > l(n + 1, vector<int>(n + 1, 0));

        int x, y;
        while (m--)
        {
            fin >> x >> y;
            a[x][y] = true;
        }

        int ans = 0;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
            {
                l[i][j] = (a[i][j]) ? 0 : l[i][j - 1] + 1;
                u[i][j] = (a[i][j]) ? 0 : u[i - 1][j] + 1;
                f[i][j] = (a[i][j]) ? 0 :
                    min(f[i - 1][j - 1] + 1, min(l[i][j], u[i][j]));
                ans = max(ans, f[i][j]);
            }
        fout << ans << endl;
        clog << ans << endl;

    }

    return 0;
}
