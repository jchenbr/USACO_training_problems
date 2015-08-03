/*
ID: jchenbr1
LANG: C++11
TASK: hidden
 */
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

#define mp(x, y) make_pair((x), (y))

int main()
{
    ifstream fin("hidden.in");
    ofstream fout("hidden.out");

    int n;
    while (fin >> n)
    {
        string str, tmp;
        while (fin >> tmp)
            str += tmp;
        vector<pair<pair<int, int>, int > > g(n);

        int m = 0;
        while ((1 << m) < n) m += 1;
        m -= 1;

        vector<vector<int> > f(m + 1, vector<int>(n, 0));

        for (int i = 0; i < n; i++)
            g[i] = mp(mp(str[i],0), i);
        sort(g.begin(), g.end());


        for (int len = 0; len <= m; len++)
        {
            int count = 0;
            for (int i = 0; i < n; i++)
            {
                if (i && g[i].first != g[i - 1].first) count += 1;
                f[len][g[i].second] = count;
            }

            for (int i = 0, j = 1 << len; i < n; i++, j++, j %= n)
                g[i] = mp(mp(f[len][i], f[len][j]), i);
            
            sort(g.begin(), g.end());
        }

        clog << g[0].second << endl;
        fout << g[0].second << endl;
    }

    return 0;
}
