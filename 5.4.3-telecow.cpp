/*
ID: jchenbr
LANG: C++11
TASK: telecow
 */
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;

struct Edge
{
    int f, c, t, nxt;
    Edge(int C, int T, int N)
        :c(C), t(T), nxt(N)
    {}
};

struct Node
{
    int beg, cur, d, c, pre;
    Node(): beg(-1){}
};

inline int L(const int &x){return x << 1;}
inline int R(const int &x){return x << 1 | 1;}

int main()
{
    ifstream fin("telecow.in");
    ofstream fout("telecow.out");

    const int inf = 1000000000 + 5;
    int n, m, s, t;
    while (fin >> n >> m >> s >> t)
    {
        s -= 1, t -= 1;
        vector<Node> a(n << 1);
        vector<Edge> e;
        e.reserve(m << 1);

        auto _func_add_edge = [&](int u, int v, int c)
        {
            e.push_back(Edge(c, v, a[u].beg));
            a[u].beg = e.size() - 1;

            e.push_back(Edge(0, u, a[v].beg));
            a[v].beg = e.size() - 1;
        };

        auto _func_max_flow = [&](int s, int t)
        {
            for (auto & node : a) 
                node.d = 0, node.cur = node.beg;
            for (auto & edge : e)
                edge.f = 0;
            vector<int> cnt(n + 1, 0);

            int u = s, v, cur, ret = 0;
            a[u].c = inf;
            cnt[0] = n;
            while (a[s].d < n)
            {
                for (cur = a[u].cur; cur != -1; cur = e[cur].nxt)
                    if (e[cur].c - e[cur].f > 0 && a[v = e[cur].t].d + 1 == a[u].d)
                        break;
                if (cur != -1)
                {
                    a[v].c = min(a[u].c, e[cur].c - e[cur].f);
                    a[v].pre = cur;

                    if ((u = v) == t)
                    {
                        do{
                            e[a[u].pre].f += a[t].c;
                            e[a[u].pre^1].f -= a[t].c;
                            u = e[a[u].pre^1].t;
                        }while (u != s);
                        ret += a[t].c;
                    }
                }else
                {
                    if (--cnt[a[u].d] == 0) break;
                    a[u].d = n, a[u].cur = a[u].beg;
                    for (cur = a[u].cur; cur != -1; cur = e[cur].nxt)
                        if (e[cur].c - e[cur].f > 0 && a[v = e[cur].t].d + 1 < a[u].d)
                            a[u].d = a[v].d + 1;
                    cnt[a[u].d] += 1;
                    if (u != s) u = e[a[u].pre^1].t;
                }
            }

            return ret;
        };

        for (int i = 0; i < n; i++)
            _func_add_edge(L(i), R(i), 1);

        n <<= 1;

        for (int i = 0; i < m; i++)
        {
            int u, v;
            fin >> u >> v;
            _func_add_edge(R(u - 1), L(v - 1), inf);
            _func_add_edge(R(v - 1), L(u - 1), inf);
        }

        int ans = _func_max_flow(R(s), L(t));
        vector<int> ans_list(ans);

        int count = 0;

        for (int i = 0; i < (n >> 1); i++)
        {
            if (i == s || i == t) continue;

            e[L(i)].c = 0;

            int tmp = _func_max_flow(R(s), L(t));

            //clog << "i = " << i <<", tmp = " << tmp << endl;

            if (count + tmp + 1 == ans)
            {
                ans_list[count++] = i + 1;
                if (count == ans) break;
            }else
                e[L(i)].c = 1;
        }

        fout << ans << endl;
        clog << ans << endl;

        for (int i = 0 ; i < ans ; i++)
        {
            if (i)
            {
                fout << " ";
                clog << " ";
            }
            fout << ans_list[i];
            clog << ans_list[i];
        }
        fout << endl;
        clog << endl;
    }

    return 0;
}
