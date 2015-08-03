/*
ID: jchenbr
LANG: C++11
TASK: milk6
 */
#include <iostream>
#include <fstream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <functional>
#include <set>
using namespace std;
typedef long long LL;

struct Edge
{
    int t, nxt, ID;
    LL c, f;
    Edge(int V, LL C, int N, int id)
        :t(V), nxt(N), ID(id), c(C)
    {}
};

struct Node
{
    int beg, cur, pre, d;
    LL c;
    Node() 
        :beg(-1), cur(-1)
    {}
};

int main()
{
    ifstream fin("milk6.in");
    ofstream fout("milk6.out");

    int n, m;
    while (fin >> n >> m)
    {
        vector<Node> a(n + 1);
        vector<Edge> e;

        e.reserve(m << 1);

        auto _func_add_edge = [&] (int u, int v, LL c,int id) -> void
        {
            e.push_back(Edge(v, c, a[u].beg, id));
            a[u].beg = e.size() - 1;

            e.push_back(Edge(u, 0, a[v].beg, -id));
            a[v].beg = e.size() - 1;
        };

        const LL inf = 1000000000LL * 1000000000LL;
        auto _func_max_flow = [&] (int s, int t)
        {
            for (auto & node : a)
                node.d = 0, node.cur = node.beg;
            for (auto & edge : e)
                edge.f = 0;

            vector<int> cnt(n + 1, 0);
            cnt[0] = n;
            a[s].c = inf;
            int u = s, v, i;
            LL tot = 0;

            while (a[s].d < n)
            {
                for (i = a[u].cur; i != -1; i = e[i].nxt)
                    if (e[i].c - e[i].f > 0 && a[v = e[i].t].d + 1 == a[u].d)
                        break;
                if (i != -1)
                {
                    a[v].pre = i;
                    a[v].c = min(a[u].c, e[i].c - e[i].f);

                    if ((u = v) == t)
                    {
                        do
                        {
                            e[a[u].pre].f += a[t].c;
                            e[a[u].pre^1].f -= a[t].c;
                            u = e[a[u].pre^1].t;
                        }while (u != s);
                        tot += a[t].c;
                    }
                }else
                {
                    if (-- cnt[a[u].d] == 0) break;
                    a[u].d = n, a[u].cur = a[u].beg;

                    for (i = a[u].cur; i != -1; i = e[i].nxt)
                        if (e[i].c - e[i].f > 0 && a[u].d > a[v = e[i].t].d + 1)
                            a[u].d = a[v].d + 1;
                    cnt[a[u].d] += 1;
                    if (u != s) u = e[a[u].pre^1].t;
                }
            }
            return tot;
        };

        for (int i = 1; i <= m; i++)
        {
            int u, v;
            LL c;
            fin >> u >> v >> c;
            //clog << "ID = " << i << ", " << u << ", " << v << ", " << c << endl;
            _func_add_edge(u , v , c * 10000 + 1, i);
        }

        LL ans = inf;
        vector<int> ans_list;
        auto find = [&](int init_e) -> void
        {
            //clog << e[(init_e - 1) << 1].ID << "," << e[(init_e - 1)<< 1].c << endl;
            LL perserve = 0;

            if (init_e)
            {
                perserve = e[(init_e - 1) << 1].c;
                e[(init_e - 1) << 1].c = 0;
            }

            LL tmp = _func_max_flow(1, n);
            //clog << init_e << ", tmp = " << tmp << ", per = " << perserve << endl; 
            if (tmp + perserve  > ans) 
            {
                if (init_e)
                    e[(init_e - 1) << 1].c = perserve;
                return;
            }

            
            ans = tmp + perserve ; 
            vector<int> tmp_list;

            if (ans == 0) return;
            vector<bool> vis(n + 1, false);

            function<void(int)> dfs = [&](int u)
            {
                if (vis[u]) return ;
                vis[u] = true;
                for (int i = a[u].beg; i!= -1; i = e[i].nxt)
                    if (e[i].c > e[i].f)
                        dfs(e[i].t);
            };

            dfs(1);
            for (int u = 1; u <= n; u++)
                if (vis[u])
                    for (int i = a[u].beg; i!= -1; i = e[i].nxt)
                        if (!vis[e[i].t] && e[i].ID > 0)
                            tmp_list.push_back(e[i].ID);
            ans_list = tmp_list;

            if (init_e)
                e[(init_e - 1) << 1].c = perserve; 
        };

        find(0);
        sort(ans_list.begin(), ans_list.end());

        clog << ans << " " <<ans_list.size() << endl;
        int count = 0;
        for (auto & an: ans_list) count += e[an].c;
        clog << "count = " << count << endl;
        if (ans > 0){
            for (int init_e = 1; init_e <= ans_list[0]; init_e++)
            {
                find(init_e);
                sort(ans_list.begin(), ans_list.end());
            }
        }
        fout << ans / 10000 << " "  << ans_list.size() << endl;
        clog << ans << " " << ans_list.size() << endl;

        for (auto & item : ans_list)
        {
            fout << item << endl;
            clog << item << endl;
        }


    }

    return 0;
}
