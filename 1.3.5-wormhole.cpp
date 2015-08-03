/*
ID: jchenbr1
LANG: C++11
TASK: wormhole
 */
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

struct Hole
{
    int x, y;
    int r_id, r_val;
    int nxt;
};

int main()
{
    ifstream fin("wormhole.in");
    ofstream fout("wormhole.out");

    int n ;
    while (fin >> n)
    {
        vector<Hole> holes(n);
        for (auto & hole : holes)
        {
            fin >> hole.x >> hole.y;
            hole.r_val = hole.x;
            hole.r_id  = -1;
            hole.nxt   = -1;
        }

        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
            {
                Hole & a = holes[i], & b= holes[j];
                if (a.y != b.y || a.x <= b.x) continue;

                if (b.r_id == -1 || a.x < b.r_val)
                {
                    b.r_val = a.x;
                    b.r_id = i;
                }
            }
        vector<bool> used(n, false);

        function<int(int)> dfs_relation = [&](int to_do)-> int
        {
            int ret = 0;
            if (to_do)
            {
                for (int i = 0; i < n; i ++)
                {
                    if (used[i]) continue;
                    for (int j = i + 1; j < n; j++)
                    {
                        if (used[j]) continue;
                        used[i] = used[j] = true;

                        holes[i].nxt = j;
                        holes[j].nxt = i;

                        ret += dfs_relation(to_do - 1);

                        holes[i].nxt = holes[j].nxt = -1;

                        used[i] = used[j] = false;
                    }
                    break;
                }
            }else 
            {
                //for (auto & h: holes)
                {
                    //clog << "(nxt=" << h.nxt << ",r=" << h.r_id << "), ";
                }
                //clog << endl;
                //clog << endl;

                for (int i = 0; i < n; i ++)
                {
                vector<vector<bool> > visited(n, vector<bool>(2, false) );

                    int u = i;
                    visited[u][0] = true;
                    //clog << u << ",";

                    while (true)
                    {
                        if (holes[u].nxt < 0) break;

                        u = holes[u].nxt;
                        if (visited[u][1])  
                        {
                            ret = 1;
                            //clog << u << ", -";
                            break;
                        }
                        visited[u][1] = true;
                        //clog << u << ",";

                        if (holes[u].r_id < 0) break;

                        u = holes[u].r_id;
                        if (visited[u][0]) 
                        {
                            ret = 1;
                            //clog << u << ", -";
                            break;
                        }
                        visited[u][0] = true;
                        //clog << u << ",";
                    } 
                    //clog << endl;
                }
            }
            return ret;
        };
        fout << dfs_relation(n >> 1) << endl;
        //clog << dfs_relation(n >> 1) << endl;
    }

    return 0;
}


