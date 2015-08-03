/*
ID: jchenbr1
LANG: C++11
TASK: comehome
 */

#include <iostream>
#include <fstream>
#include <cstring>
#include <ctype.h>
#include <vector>
#include <map>
#include <queue>
using namespace std;

const int inf = 1000000000 + 5;
using namespace std;

struct Node
{
    int f;
    map<int, int> nxt;
    char name;

    Node(char n)
    {
        f = inf;
        name = n;
    }

    void insertNxt(int v, int distance)
    {
        if (nxt.count(v) == 0 || nxt[v] > distance)
            nxt[v] = distance;
    }
};

int main()
{
    ifstream fin("comehome.in");
    ofstream fout("comehome.out");

    int m;
    while (fin >> m)
    {
        vector<Node> node;
        map<char, int> name_to_id;
        char u, v;
        int d;
        while (m--)
        {
            fin >> u >> v >> d;
            if (name_to_id.count(u) == 0)
            {
                name_to_id[u] = node.size();
                node.push_back(Node(u));
            }
            if (name_to_id.count(v) == 0)
            {
                name_to_id[v] = node.size();
                node.push_back(Node(v));
            }
            node[name_to_id[u]].insertNxt(name_to_id[v], d);
            node[name_to_id[v]].insertNxt(name_to_id[u], d);
        }
        int x = name_to_id['Z'];
        node[x].f = 0;
        queue<int> que;
        que.push(x);
        while (!que.empty())
        {
            x = que.front();
            //clog << "x = " << x << ", name = " << node[x].name << ", f = " << node[x].f << endl;
            que.pop();
            for (const auto &e: node[x].nxt)
                if (node[x].f + e.second < node[e.first].f)
                {
                    node[e.first].f = node[x].f + e.second;
                    que.push(e.first);
                }
        }
        int ans = inf;
        char ans_name;
        for (auto & n : node)
            if (isupper(n.name) && n.name != 'Z' && n.f < ans)
                ans = n.f, ans_name = n.name;

        clog << ans_name << " " << ans << endl;
        fout << ans_name << " " << ans << endl;
    }

    return 0;
}
