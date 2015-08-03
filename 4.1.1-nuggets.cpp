/*
ID: jchenbr1
LANG: C++11
TASK: nuggets
 */
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    ifstream fin("nuggets.in");
    ofstream fout("nuggets.out");

    int n ;
    while (fin >> n)
    {
        vector<int> a(n);
        for (auto & item : a) fin >> item;
        sort(a.begin(), a.end());

        int m = a.back();
        vector<bool> f(m, false);
        vector<int> nxt(m);
        vector<int> prv(m);

        for (int i = 0; i < m; i++)
        {
            nxt[i] = (i + 1) % m;
            prv[i] = (i + m - 1) % m;
        }

        f[0] = true;
        nxt[prv[0]] = nxt[0];
        prv[nxt[0]] = prv[0];

        int u = 1 % m, cumsum = 1, now = 1, ans = -1;
        clog << "? m = " << m << endl;
        while (true)
        {
            //clog << "u = " << u << ", now = " << now << ", cumsum = " << cumsum  << endl;
            if (f[u]) {cumsum = 0;break;}
            if (cumsum >= m) break;

            for (auto & j : a)
                if (now >= j && f[(u + m - j)%m])
                {
                    f[u] = true;
                    cumsum = 0;
                    break;
                }
            //clog << "\t" << f[u] << endl;

            if (f[u])
            {
                nxt[prv[u]] = nxt[u];
                prv[nxt[u]] = prv[u];
            }else
                ans = max(ans, now);

            int to_go = nxt[u] - u;
            if (to_go <= 0) to_go += m;
            cumsum += to_go;
            now += to_go;
            u = nxt[u];
        }

        if (cumsum >= m || ans < 0)
        {
            clog << 0 << endl;
            fout << 0 << endl;
        }else
        {
            clog << ans << endl;
            fout << ans << endl;
        }
    }

    return 0;
}
