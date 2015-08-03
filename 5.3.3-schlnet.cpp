/*
ID: jchenbr1
LANG: C++11
TASK: schlnet
 */
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

int main()
{
    ifstream fin("schlnet.in");
    ofstream fout("schlnet.out");

    int n ;
    while (fin >> n)
    {
        vector<vector<int> > nxt(n);
        vector<vector<int> > last(n);
        vector<int> in(n, 0);
        vector<int> out(n, 0);
        int  v;
        for (int i = 0; i < n; i++)
        {
            while (fin >> v, v!=  0)
            {
                v -= 1;
                nxt[i].push_back(v);
                last[v].push_back(i);
                in[v] += 1;
                out[i] += 1;
            }
        }

        vector<bool> vis(n, false);
        function<bool(int)> dfs = [&](int u)
        {
            if (vis[u]) return false;
            vis[u] = true;
            for (auto & v : nxt[u])
                dfs(v);

            return true;
        };

        int ans_1 = 0;
        for (int i = 0; i < n; i++)
            if (in[i] == 0)
            {
                ans_1 += 1;
                dfs(i);
            }

        

        function< pair<int, int>(int) > dfs_2 = [&](int u) -> pair<int, int>
        {
            if (vis[u]) return make_pair(0, 0);
            //clog << u + 1 << " ";
            vis[u] = true;

            pair<int, int> ret = make_pair(in[u] == 0,out[u] == 0);

            for (auto & v: nxt[u])
            {
                auto tmp = dfs_2(v);
                ret.first += tmp.first;
                ret.second += tmp.second;
            }

            for (auto & v: last[u])
            {
                auto tmp = dfs_2(v);
                ret.first += tmp.first;
                ret.second += tmp.second;
            }

            return ret;
        };

        for (int i = 0; i < n; i++)
            if (!vis[i])
                ans_1 += 1, dfs_2(i);

        vis = vector<bool>(n, false);
        vector<pair<int, int> > ans_list;

        for (int i = 0; i < n; i++)
            if (!vis[i])
            {
                ans_list.push_back(dfs_2(i));
            }

        int ans_2 = 0;

        if (ans_list.size() == 1)
        {
            ans_2 = max(ans_list[0].first, ans_list[0].second);
        }else {
            int x = 0, y = 0;
            for (auto & pr : ans_list)
            {
                x += max(1, pr.first);
                y += max(1, pr.second);
            }
            ans_2 = max(x, y);
        }

        fout << ans_1 << endl << ans_2 << endl;
        clog << ans_1 << endl << ans_2 << endl;
    }


    return 0;
}
