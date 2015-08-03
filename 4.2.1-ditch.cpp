/*
ID: jchenbr1
LANG: C++11
TASK: ditch
 */
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

struct Edge
{
    int t, c, nxt;
    Edge(int V, int C, int N):t(V), c(C), nxt(N){}
};

struct Node
{
    int beg, cur, pre, c, d;
    Node():beg(-1), cur(-1){};
};

int main()
{
    ifstream fin("ditch.in");
    ofstream fout("ditch.out");

    int n, m;
    while (fin >> m >> n)
    {
        vector<Node> a(n);
        vector<Edge> e;

        e.reserve(m << 1);

        auto _func_add_edge = [&](int u, int v, int c)-> void
        {
            e.push_back(Edge(v, c, a[u].beg));
            a[u].beg = e.size() - 1;

            e.push_back(Edge(u, 0, a[v].beg));
            a[v].beg = e.size() - 1;
        };

        auto _func_max_flow = [&](int s,int t)
        {
            for (auto & node: a) 
                node.d = 0, node.cur = node.beg;

            vector<int> cnt(n + 1, 0);
            cnt[0] = n;
            const int inf = 1000000000;
            a[s].c = inf;
            int u = s, v, tot = 0, i;

            while (a[s].d < n)
            {
                //clog << "u = " << u << ", tot = " << tot << endl; 
                for (i = a[u].cur; i >= 0; i = e[i].nxt)
                    if (e[i].c && a[v = e[i].t].d + 1 == a[u].d)
                        break;
                if (i >= 0)
                {
                    a[v].pre = i;
                    a[v].c = min(a[u].c, e[i].c);

                    if ((u = v) == t)
                    {
                        do
                        {
                            e[a[u].pre].c -= a[t].c;
                            e[a[u].pre^1].c += a[t].c;
                            u = e[a[u].pre^1].t;
                        }while (u != s);
                        tot += a[t].c;
                    }
                }else
                {
                    if (-- cnt[a[u].d] == 0) break;
                    a[u].d = n, a[u].cur = a[u].beg;

                    for (i = a[u].cur; i >= 0; i = e[i].nxt)
                        if (e[i].c && a[u].d > a[v = e[i].t].d + 1)
                            a[u].d = a[v].d + 1;

                    cnt[a[u].d] += 1;
                    if (u != s) u = e[a[u].pre^1].t;
                }
            }
            return tot;
        };

        while (m--)
        {
            int u, v, c;
            fin >> u >> v >> c;
            _func_add_edge(u - 1, v - 1, c);
        }
        int ans = _func_max_flow(0, n - 1);
        fout << ans << endl;
        clog << ans << endl;
    }

    return 0;
}
