/*
ID: jchenbr1
LANG: C++11
TASK: tour
 */
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>
#include <string>
using namespace std;

struct Edge
{
    int c, t, cost, nxt;
    Edge(int C, int T, int CST, int NXT)
        : c(C), t(T), cost(CST), nxt(NXT)
    {}
};

struct Node
{
    int cur, beg, c, pre;
    Node():beg(-1){}
};

inline int L(const int & x) {return x << 1;}
inline int R(const int & x) {return x << 1 | 1;}

int main()
{
    ifstream fin("tour.in");
    ofstream fout("tour.out");

    int n, m;
    while (fin >> n >> m)
    {
        map<string, int> name_id;

        vector<Node> a(n << 1);
        vector<Edge> e;
        e.reserve(m << 1);

        auto _func_add_edge = [&](int u, int v, int c, int cost)
        {
            //clog << "(" << u << ", " << v << ") = " << c << ", " << cost << endl;
            e.push_back(Edge(c, v, cost, a[u].beg));
            a[u].beg = e.size() - 1;

            e.push_back(Edge(0, u, -cost, a[v].beg));
            a[v].beg = e.size() - 1;
        };

        for (int i = 0; i < n; i++)
        {
            string name ;
            fin >> name;
            name_id[name] = i;

            if (i == 0)
                _func_add_edge(L(i), R(i), 2, 0);
            else if (i == n - 1)
                _func_add_edge(L(i), R(i), 2, 1);
            else
                _func_add_edge(L(i), R(i), 1, 1);
        }

        for (int i = 0; i < m; i++)
        {
            string name;
            fin >> name;
            int u = name_id[name];
            fin >> name;
            int v = name_id[name];

            if (u > v) swap(u, v);

            _func_add_edge(R(u), L(v), 1, 0);
        }

        n <<= 1;
        auto _func_max_flow = [&](int s, int t) -> int
        {
            const int inf = 1000000000 + 5;
            vector<int> opt;
            vector<int> que;

            que.reserve(n << 2);
            int ret = 0, count = 0;

            do
            {
                int u = s, v;
                opt = vector<int> (n, -1);
                opt[u] = 0;

                int fi = 0;
                que.clear();
                que.push_back(u);

                while (fi < (int)que.size())
                {
                    u = que[fi++];
                    for (int cur = a[u].beg; v = e[cur].t, cur != -1; cur = e[cur].nxt)
                        if (e[cur].c && opt[u] + e[cur].cost > opt[v])
                        {
                            opt[v] = opt[u] + e[cur].cost;
                            a[v].pre = cur;
                            que.push_back(v);
                        }
                }

                //for (int i = 0 ; i < n; i++) clog << opt[i] << " "; clog << endl;
                //clog << "opt[t] = " << opt[t] << ", t = " << t << endl;
                if (opt[t] < 0) break;

                int flow = inf;
                for (u = t; u != s; u = e[a[u].pre^1].t)
                    flow = min(flow, e[a[u].pre].c);

                for (u = t; u != s; u = e[a[u].pre^1].t)
                {
                    e[a[u].pre].c -= flow;
                    e[a[u].pre^1].c += flow;
                }

                clog << "flow = " << flow << endl;

                count += flow;
                ret += flow * opt[t];
            }while (opt[t] >= 0);
            if (count < 2) return 1;
            return ret;
        };

        int ans = _func_max_flow(L(0), n - 1);
        fout << ans << endl;
        clog << ans << endl;


    }

    return 0;
}
