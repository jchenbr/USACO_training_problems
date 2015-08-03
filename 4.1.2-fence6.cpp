/*
ID: jchenbr1
LANG: C++11
TASK: fence6
 */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <functional>
using namespace std;

int main()
{
    ifstream fin("fence6.in");
    ofstream fout("fence6.out");

    int m;
    while (fin >> m)
    {
        vector<pair<pair<int,int>, int> > edge;
        map<string, int> str2id;

        int NID = 0;

        for (int k = 0; k < m; k++)
        {
            int ID, len, L, R, LID, RID;
            fin >> ID >> len >> L >> R;

            vector<int> l(L + 1);
            l[0] = ID;
            for (int i = 1; i <= L; i++) fin >> l[i];
            sort(l.begin(), l.end());
            string str;
            for (auto & item : l) str += to_string(item);
            if (str2id.count(str) == 0) 
                str2id[str] = NID++;
            LID = str2id[str];
                
            vector<int> r(R + 1);
            r[0] = ID;
            for (int i = 1; i <= R; i++) fin >> r[i];
            sort(r.begin(), r.end());
            str.clear();
            for (auto & item : r) str += to_string(item);
            if (str2id.count(str) == 0)
                str2id[str] = NID++;
            RID = str2id[str];

            edge.push_back(make_pair(make_pair(LID, RID),len));
        }
        int n = NID;
        const int inf = 1000000000;

        vector<pair<int, int> > e(m);
        vector<vector<int> > nxt(n);
        for (int i = 0; i < m; i++)
        {
            int u = edge[i].first.first, v = edge[i].first.second;
            e[i].first = u + v;
            e[i].second = edge[i].second;
            //clog << "len = " << e[i].second << endl; 
            nxt[u].push_back(i);
            nxt[v].push_back(i);
        }

        vector<bool> vis(n, false);
        vector<bool> used(m, false);
        int ans = inf;
        function<void(int, int)> dfs = [&](int u, int tot)
        {
            if (tot >= ans) return ;
            //clog << "\t" << u << ", " << tot << endl;

            for (auto & i: nxt[u])
              if (!used[i])
              {
                  int v = e[i].first - u;
                  if (vis[v])
                  {
                      ans = min(ans, tot + edge[i].second);
                  }else
                  {
                      used[i] = true;
                      vis[v] = true;

                      dfs(v, tot + edge[i].second);

                      vis[v] = false;
                      used[i] = false;
                  }
              }  
        };

        for (int i = 0; i < n; i++) 
        {
            vis[i] = true;
            //clog << "i = " << i << endl;
            dfs(i, 0);
            vis[i] = false;
        }

        fout << ans << endl;
        clog << ans << endl;
    }

    return 0;
}
