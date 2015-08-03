/*
ID: jchenbr1
LANG: C++11
TASK: theme
 */
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

int main()
{
    ifstream fin("theme.in");
    ofstream fout("theme.out");

    int n;
    while (fin >> n)
    {
        vector<int> a(n + 1);
        for (int i = 1; i <= n; i++) fin >> a[i];

        vector<vector<int> > f(2, vector<int>(n + 1, 1));

        int ans = 0;
        for (int i = 2; i <= n; i++)
            for (int j = 2; j < i; j++)
                if (a[i] - a[i - 1] == a[j] - a[j - 1])
                {
                    f[i & 1][j] = min(f[~i & 1][j - 1] + 1, i - j);
                    ans = max(ans, f[i & 1][j]);
                }else 
                    f[i & 1][j] = 1;
        if (ans < 5) ans = 0;
        fout << ans << endl;
        clog << ans << endl;
    }

    return 0;
}
