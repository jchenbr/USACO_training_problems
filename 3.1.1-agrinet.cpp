/*
ID: jchenbr1
LANG: C++11
TASK: agrinet
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

int main()
{
    ifstream fin("agrinet.in");
    ofstream fout("agrinet.out");

    int n;
    while (fin >> n)
    {
        vector<vector<int> > path(n, vector<int>(n));

        for (auto & row: path)
            for (auto & d: row) 
                fin >> d;

        const int inf = 1000000000;
        vector<int> opt(n, inf);
        vector<bool> vis(n, false);
        set<pair<int, int> > ob;

        int u = 0, ans = 0;
        opt[u] = 0;
        ob.insert(make_pair(0, u));

        while (!ob.empty())
        {
            u = ob.begin() -> second;
            ob.erase(ob.begin());

            if (vis[u]) continue;
            vis[u] = true;
            ans += opt[u];

            for (int v = 0; v < n; v++)
                if (!vis[v] && path[u][v] < opt[v])
                    opt[v] = path[u][v], ob.insert(make_pair(path[u][v], v));
        }

        fout << ans << endl;
        clog << ans << endl;
    }

    return 0;
}
