/*
ID: jchenbr1
LANG: C++11
TASK: milk4
 */
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <functional>
#include <cstring>
using namespace std;

int main()
{
    ifstream fin("milk4.in");
    ofstream fout("milk4.out");

    int m, n;
    while (fin >> m >> n)
    {
        vector<int> a(n);
        for (auto & item : a) fin >> item;
        sort(a.begin(), a.end());

        const int inf = 1000000000;
        int f[m + 1], g[m + 1], opt_g[m + 1], last_f[m + 1], last_g[m + 1];
        for (int i = 0; i <= m; i++) f[i] = g[i] = inf;
        g[0] = 0;
        memset(last_g, 0, sizeof(last_g));
        memset(opt_g, 0, sizeof(opt_g));

        function<bool(int, int)> cmp = [&](int u, int v)
        {
            if (u == 0) 
                return true;
            if (v == 0)
                return false;
            if (opt_g[u] == opt_g[v])
                return cmp(last_g[u], last_g[v]);
            return opt_g[u] < opt_g[v];
        };

        for (int i = n - 1; i >= 0; i--)
        {

            for (int j = 0; j < a[i]; j++)
            {
                f[j] = g[j] + 1;
                last_f[j] = j;
            }

            for (int j = a[i]; j <= m; j++)
            {
                if (f[j - a[i]] < g[j - a[i]] + 1 ||
                        (
                         f[j - a[i]] == g[j - a[i]] + 1 && 
                         cmp(last_f[j - a[i]], j - a[i])
                         )
                   )
                {
                    f[j] = f[j - a[i]];
                    last_f[j] = last_f[j - a[i]];
                }else
                {
                    f[j] = g[j - a[i]] + 1;
                    last_f[j] = j - a[i];
                }
            }
#if 0
            clog << "a = " << a[i] << endl;
            for (int j = 0; j <= m; j++)
                clog << "(" << f[j] << ", " << last_f[j] <<") " << endl;
#endif

            for (int j = 0; j <= m; j++)
            {
                if (f[j] <= g[j])
                {
                    g[j] = f[j];
                    last_g[j] = last_f[j];

                    opt_g[j] = a[i]; 
                }
            }
        }


        fout << g[m];
        clog << g[m];
        vector<int> ans;
        ans.reserve(g[m]);
        int now = m;
        while (now != 0)
        {
            ans.push_back(opt_g[now]);
            now = last_g[now];
        }
        sort(ans.begin(), ans.end());
        for (auto & item: ans) 
        {
            fout << " " << item;
            clog << " " << item;
        }
        fout << endl;
        clog << endl;
    }

    return 0;
}
