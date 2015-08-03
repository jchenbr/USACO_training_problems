/*
ID: jchenbr
LANG: C++11
TASK: race3
 */
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

int main()
{
    ifstream fin("race3.in");
    ofstream fout("race3.out");

    int n = 0, tmp;
    vector<vector<int> > nxt(1);
    while (fin >> tmp)
    {
        if (tmp == -1) 
        {
            break;
        }
        else if (tmp == -2) 
        {
            n += 1;
            nxt.push_back(vector<int>(0));
        }
        else
            nxt[n].push_back(tmp);
    }
    n -= 1;

    auto check = [&](int pivot)
    {
        vector<int> vis(n + 1, 0);

        function<bool(int, int, int)> dfs = [&](int u, int forbid, int stamp)
        {
            if (u == forbid) return true;
            if (vis[u]) return vis[u] == stamp;
            vis[u] = stamp;
        
            for (auto & v : nxt[u])
                if (!dfs(v, forbid, stamp))
                    return false;
            return true;
        };

        dfs(0, pivot, 1);
        if (vis[n]) return 0;

        if (!dfs(pivot, -1, 2)) return 1;

        return 3;
    };

    vector<int> unavoid, split;
    for (int i = 1; i < n; i++)
    {
        int flag = check(i);
        if (flag > 0)
        {
            unavoid.push_back(i);
            if (flag > 1)
                split.push_back(i);
        }
    }

    fout << unavoid.size(); 
    clog << unavoid.size();
    for (int i = 0; i < (int)unavoid.size(); i++)
    {
        fout << " " << unavoid[i];
        clog << " " << unavoid[i];
    }
    fout << endl;
    clog << endl;

    fout << split.size();
    clog << split.size();
    for (int i = 0; i < (int)split.size(); i++)
    {
        fout << " " << split[i];
        clog << " " << split[i];
    }
    fout << endl;
    clog << endl;

    return 0;
}
