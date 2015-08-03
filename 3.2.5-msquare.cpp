/*
ID: jchenbr1
LANG: C++11
TASK: msquare
 */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <queue>
using namespace std;

int main()
{
    ifstream fin("msquare.in");
    ofstream fout("msquare.out");

    auto id_to_vec = [](int id)
    {
        vector<int> ret(8);
        for (auto & item: ret) item = id % 10, id/=10;
        return ret;
    };

    auto vec_to_id = [](const vector<int> & vec)
    {
        int pos = 1, ret = 0;
        for (auto & item: vec) ret += pos * item, pos *=10;
        return ret;
    };

    auto rotate_vec = [](const vector<int> & vec)
    {
        vector<int> ret(vec);
        ret[1] = vec[5];
        ret[2] = vec[1];
        ret[6] = vec[2];
        ret[5] = vec[6];

        return ret;
    };

    auto shift_vec = [](const vector<int> & vec)
    {
        vector<int> ret(8);
        for (int i = 0; i < 4; i++)
        {
            ret[i] = vec[(i + 4 + 1) % 4];
            ret[i + 4] = vec[(i + 4 + 1) % 4 + 4];
        }
        return ret;
    };

    auto exchange_vec = [](const vector<int> & vec)
    {
        vector<int> ret(8);
        for (int i = 0; i < 8; i++)
            ret[i] = vec[(i + 4) % 8];
        return ret;
    };

    vector<int> vec(8), nxt;
    int id, nid;
    map<int, string> vis;
    queue<int> que;

    que.push(12348765);
    vis[12348765] = "";
    clog << vec_to_id(exchange_vec(id_to_vec(12348756))) << endl;
    clog << vec_to_id(shift_vec(id_to_vec(12348765))) << endl;
    clog << vec_to_id(rotate_vec(id_to_vec(12348765))) << endl;
    
    while (!que.empty())
    {
        id = que.front();
        vec = id_to_vec(id);
        
        //clog << "id = " << id << endl;

        que.pop();

        nxt = exchange_vec(vec);
        nid = vec_to_id(nxt);
        if (vis.count(nid) == 0)
            vis[nid] = vis[id] + "A", que.push(nid);

        nxt = shift_vec(vec);
        nid = vec_to_id(nxt);
        if (vis.count(nid) == 0)
            vis[nid] = vis[id] + "B", que.push(nid);

        nxt = rotate_vec(vec);
        nid = vec_to_id(nxt);
        if (vis.count(nid) == 0)
            vis[nid] = vis[id] + "C", que.push(nid);
    }

    for (int i = 7; i >= 4; i--) fin >> vec[i];
    for (int i = 0; i < 4; i++) fin >> vec[i];
    clog << "Final = " << vec_to_id(vec) << endl;
    string str = vis[vec_to_id(vec)];
    fout << str.size() << endl;
    for (int i = 0 ; i < (int)str.size(); i++)
    {
        if (i && i % 60 == 0) fout << endl, clog << endl;
        fout << str[i];
        clog << str[i];
    }
    fout << endl;
    clog << endl;

    return 0;
}
