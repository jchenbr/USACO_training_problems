/*
ID: jchenbr1
LANG: C++11
TASK: range
 */
#include <iostream>
#include <cstdio>
#include <string>
#include <fstream>
#include <vector>
#include <cctype>
using namespace std;

int main()
{
    ifstream fin("range.in");
    ofstream fout("range.out");

    int n;
    while (fin >> n)
    {
        vector<vector<int> > a(n + 2, vector<int>(n + 2, 0));
        vector<vector<int> > l(a), u(a), f(a);
        vector<int > ans(n + 1, 0);

        clog << "n = " << n << endl;
        for (int i = 1; i <= n; i++ )
            for (int j = 1; j <= n; j++)
            {
                char d;
                while (fin >> d)
                    if (isdigit(d)) break;
                a[i][j] = d - '0';
        //        clog << a[i][j];
                if (a[i][j])
                {
                    u[i][j] = u[i - 1][j] + 1;
                    l[i][j] = l[i][j - 1] + 1;
                    f[i][j] = min(f[i - 1][j - 1] + 1, min(u[i][j], l[i][j]));
                    ans[f[i][j]] += 1;
                }
            }
        for (int i = n - 1; i >= 2; i--) ans[i] += ans[i + 1];
        for (int i = 2; i <=n; i++)
            if (ans[i])
        {
            fout << i << " " << ans[i] << endl;
            clog << i << " " << ans[i] << endl;
        }
    }

    return 0;
}
