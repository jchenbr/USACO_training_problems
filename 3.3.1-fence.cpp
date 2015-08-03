/*
ID: jchenbr1
LANG: C++11
TASK: fence
 */
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <stack>
using namespace std;

int main()
{
    ifstream fin("fence.in");
    ofstream fout("fence.out");

    int m, n = 500;
    while (fin >> m)
    {
        vector<vector<int> > nxt(n + 1);
        vector<int> e(m);
        int u, v;
        for (int i = 0; i < m; i++)
        {
            fin >> u >> v;
            e[i] = u + v;
            nxt[u].push_back(i);
            nxt[v].push_back(i);
        }

        clog << "?" << endl;

        stack<int> to_do;
        for (int i = 1; i <= n; i++)
        {
            for (auto x = begin(nxt[i]); x!= end(nxt[i]); x++)
                for (auto y = next(x); y != end(nxt[i]); y++)
                    if (e[*x] > e[*y])
                        swap(*x, *y);
        }

        for (int i = 0; i < n; i++)
            if ((nxt[i].size() & 1) == 1)
            {
                to_do.push(i);
                break;
            }

        if (to_do.size() == 0)
            for (int i = 0; i < n; i++)
                if (nxt[i].size() > 0)
                {
                    to_do.push(i);
                    break;
                }


        vector<int> ans;
        vector<bool> vis(m, false);

        ans.reserve(m + 1);

        while (!to_do.empty())
        {
            clog << "u = " << u << endl;
            int u = to_do.top();
            bool flag = false;

            for (auto & nx: nxt[u])
            {
                if (vis[nx])
                    continue;

                vis[nx] = true;
                flag = true;

                int v = e[nx] - u;
                to_do.push(v);
                break;
            }

            if (!flag)
            {
                to_do.pop();
                ans.push_back(u);
            }
        }

        for (auto it = ans.rbegin(); it != ans.rend(); it ++)
        {
            fout << *it << endl;
            clog << *it << endl;
        }
    }

    return 0;
}
