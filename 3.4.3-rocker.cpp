/*
ID: jchenbr1
LANG: C++11
TASK: rockers
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>

using namespace std;

int main()
{
    ifstream fin("rockers.in");
    ofstream fout("rockers.out");

    int n, m, t;
    while (fin >> n >> t >> m)
    {
        int song[n + 1];
        for (int i = 1; i <= n; i++) fin >> song[i];

        int f[n + 1][m + 1][t + 1] ;

        memset(f, 0, sizeof(f));

        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j ++)
            {
                for (int k = 0; k <= t; k++)
                {

                    f[i][j][k] = max(f[i][j - 1][t], f[i - 1][j][k]);

                    if (k >= 1)
                        f[i][j][k] = max(f[i][j][k], f[i][j][k - 1]);

                    if (k >= song[i])
                        f[i][j][k] = max(f[i][j][k], f[i - 1][j][k - song[i]] + 1);

                    //clog << "(" << i << ", " << j << ", " << k << ") = "<< f[i][j][k] << endl;
                }
            }
        }
        clog << f[n][m][t] << endl;
        fout << f[n][m][t] << endl;
    }

    return 0;
}

