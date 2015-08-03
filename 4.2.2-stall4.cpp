/*
ID: jchenbr1
LANG: C++11
TASK: stall4
 */
#include <iostream>
#include <fstream>
#include <vector>
#include <functional>
using namespace std;

int main()
{
    ifstream fin("stall4.in");
    ofstream fout("stall4.out");

    int n, m;
    while (fin >> n >> m)
    {
        vector<vector<int> > nxt(n);

        for (auto & nx: nxt)
        {
            int num;
            fin >> num;
            nx.resize(num);
            for (auto &v: nx)
                fin >> v, v -= 1;
        }

        vector<int> opt(m, -1);
        vector<int> vis(n, false);


        function<bool(int u)> find = [&](int u)
        {
            if (vis[u]) return false;
            vis[u] = true;

            for (auto & v: nxt[u])
            {
                if ((opt[v] < 0)||find(opt[v]))
                {
                    opt[v] = u;
                    return true;
                }
            }

            return false;
        };

        int ans = 0;
        for (int i = 0; i < n; i++)
        {
            for (auto & item : vis) item = false;
            ans += find(i);
        }
        fout << ans << endl;
        clog << ans << endl;
    }

    return 0;
}
