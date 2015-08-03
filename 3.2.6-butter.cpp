/*
ID: jchenbr1
LANG: C++11
TASK: butter
 */
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;

int main()
{
    ifstream fin("butter.in");
    ofstream fout("butter.out");

    int N, M, C;
    while (fin >> C >> N >> M)
    {
        vector<int> cows(C);
        for (auto & item : cows) fin >> item, item -= 1;

        vector<vector<pair<int,int> > > nxt(N);

        int x, y, z;
        for (int i = 0; i < M; i++)
        {
            fin >> x >> y >> z;
            x -= 1, y -= 1;
            nxt[x].push_back(make_pair(y, z));
            nxt[y].push_back(make_pair(x, z));
        }

        vector<int> cost(N, 0);

        const int inf = 1000000000;
        for (auto & cow: cows) 
        {
            queue<int> que;
            vector<int> opt(N, inf);

            int u = cow;
            que.push(u);
            opt[u] = 0;

            while (!que.empty())
            {
                u = que.front();
                que.pop();
                for (const auto & pr: nxt[u])
                    if (opt[u] + pr.second < opt[pr.first])
                    {
                        opt[pr.first] = opt[u] + pr.second;
                        que.push(pr.first);
                    }
            }

            for (int i = 0; i < N; i++) cost[i] +=  opt[i];
        }
        int best = 0;
        for (int i = 0; i < N; i++) if (cost[i] < cost[best]) best = i;
        clog << cost[best] << endl;
        fout << cost[best] << endl;
    }

    return 0;
}
