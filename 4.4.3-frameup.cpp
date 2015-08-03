/*
ID: jchenbr1
LANG: C++11
TASK: frameup
 */
#include <iostream>
#include <cstdio>
#include <string>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <cctype>
#include <algorithm>
#include <functional>
#include <set>
using namespace std;

int main()
{
    ifstream fin("frameup.in");
    ofstream fout("frameup.out");

    int n, m;
    while (fin >> n >> m)
    {
        vector<int> lim(26, 0);
        vector<int> l(26, m), r(26, 0), u(26, n), d(26, 0);
        set<int> apr;
    
        vector<vector<int> > pic(n, vector<int>(m, 26) );

        for (int i = 0; i < n; i++)
        {
            string str;
            fin >> str;
            for (int j = 0; j < m; j++)
                if (isupper(str[j]))
                {
                    int val = pic[i][j] = str[j] - 'A';
                    lim[val] += 1;
                    apr.insert(val);
                    l[val] = min(l[val], j);
                    r[val] = max(r[val], j);
                    u[val] = min(u[val], i);
                    d[val] = max(d[val], i);
                }
        }

        vector<bool> used(27, false);
        
        vector<string> ans;
        string now;
        now.resize(apr.size());

        vector<vector<bool> > path(26, vector<bool>(26, 0));
        vector<int> in(26, -1);

        for (auto & cur : apr)
        {
            in[cur] = 0;
            for (int i = u[cur]; i <= d[cur]; i++)
            {
                for (int j = l[cur]; j <= r[cur]; j += (i == u[cur] || i == d[cur]) ? 1 : r[cur] - l[cur])
                    if (pic[i][j] != cur)
                        path[cur][pic[i][j]] = true;
            }

        }
        for (auto & u: apr)
            for (auto & v: apr)
                if (path[u][v]) in[v] += 1;

        for (auto & u: apr)
        {
            for (auto & v: apr)
                clog << path[u][v] << " ";
            clog << endl;
        }
        for (auto & u: apr)
            clog << (char)('A' + u) << " " << in[u] << endl;


        function<void(int, int)> dfs = [&](int u, int lv)
        {
            //clog << "lv = " << lv << ", u = " << (char)('A' + u) << endl;
            if (lv == (int)apr.size())
                ans.push_back(now);
            else
            {
                used[u] = true;

                for (auto & v : apr)
                    if (path[u][v]) in[v] -= 1;

                for (auto & v : apr)
                    if (in[v] == 0 && !used[v])
                        now[lv] = 'A' + v,dfs(v, lv + 1);

                for (auto & v : apr)
                    if (path[u][v]) in[v] += 1;

                used[u] = false;
            }
        };

        for (auto & u : apr)
            if (in[u] == 0)
                now[0] = 'A' + u, dfs(u, 1);

        for (auto & s : ans)
            fout << s << endl, clog << s << endl;

    }

    return 0;
}

