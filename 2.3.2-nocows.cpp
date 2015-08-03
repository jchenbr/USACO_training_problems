/*
ID: jchenbr1
LANG: C++11
TASK: nocows
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    ifstream fin("nocows.in");
    ofstream fout("nocows.out");

    int n, m;
    while (fin >> n >> m)
    {
        vector<vector<int> > f(m + 1, vector<int>(n + 1, 0));
        vector<int> g(n + 1, 0); 

        f[1][1] = g[1] = 1;

        for (int h = 2; h <= m; h ++)
            for (int i = n; i >= h; i--)
            {
                int tot = i - 1;

                for (int l = h - 1; l < tot; l++)
                {
                    f[h][i] += f[h - 1][l] * g[tot - l] * 2 - f[h - 1][l] * f[h - 1][tot - l];
                    f[h][i] %= 9901;
                }

                g[i] += f[h][i];
            g[i] %= 9901;
                if (f[h][i]) clog << "(height = " << h << ", n = " << i << ") =" << f[h][i] << endl;
            }

        clog << f[m][n] << endl;
        fout << f[m][n] << endl;
    }

    return 0;
}
