/*
ID: jchenbr1
LANG: C++11
TASK: game1
 */
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main()
{
    ifstream fin("game1.in");
    ofstream fout("game1.out");

    int n ;
    while (fin >> n)
    {
        vector<int> a(n + 1);
        vector<int> sum(n + 1, 0);
        for (int i = 1; i <= n; i++)
            fin >> a[i], sum[i] = sum[i - 1] + a[i];

        vector<vector<int> > f(n + 1, vector<int>(n + 1, 0));
        for (int len = 0; len < n; len ++)
            for (int l = 1; l + len <= n; l++)
            {
                int r = l + len;
                if (l == r)
                    f[l][r] = sum[r] - sum[l - 1];
                else
                    f[l][r] = sum[r] - sum[l - 1] - min(f[l + 1][r], f[l][r - 1]);
            }
        fout << f[1][n] << " " << sum[n] - f[1][n]<< endl;
        clog << f[1][n] << " " << sum[n] - f[1][n]<< endl;
    }

    return 0;
}
