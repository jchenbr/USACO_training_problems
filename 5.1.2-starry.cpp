/*
ID: jchenbr1
LANG: C++11
TASK: starry
 */
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>
#include <functional>

using namespace std;

typedef pair<pair<int, int>, string> Cluster;

Cluster rotate(const Cluster & c)
{
    pair<int, int> sz(c.first);
    string str;
    str.resize(sz.first * sz.second);
    for (int i = 0; i < sz.first; i++)
        for (int j = 0; j < sz.second; j++)
            str[(sz.second - j - 1) * sz.first + i] = c.second[i * sz.second + j];

    swap(sz.first, sz.second);
    return Cluster(sz, str);
}

Cluster flip(const Cluster & c)
{
    pair<int, int> sz(c.first);
    string str;
    str.resize(sz.first * sz.second);
    for (int i = 0; i < sz.first; i++)
        for (int j = 0; j < sz.second; j++)
            str[i * sz.second + sz.second - j - 1] = c.second[i * sz.second + j];

    return Cluster(sz, str);
}

Cluster build(const vector<pair<int, int> > vec)
{
    int l = 10000, r = 0, u = 10000, d = 0;
    for (auto & pr: vec)
    {
        l = min(l, pr.second);
        r = max(r, pr.second);
        u = min(u, pr.first);
        d = max(d, pr.first);
    }

    int h = d - u + 1, w = r - l + 1;

    string str;
    str.resize(h * w);

    for (auto & ch: str) ch = '0';
    for (auto & pr: vec) str[(pr.first - u) * w + pr.second - l] = '1';

    return Cluster(make_pair(h, w), str);
}

int main()
{
    ifstream fin("starry.in");
    ofstream fout("starry.out");

    int n, m;
    while (fin >> m >> n)
    {
        vector<string> pic(n);
        for (auto & row: pic) fin >> row;

        vector<vector<bool> > vis(n, vector<bool>(m, false));

        map<Cluster, char> apr;

        function<void(int, int, vector<pair<int,int> > &)>
            dfs = [&](int x, int y, vector<pair<int, int> > & flash)
            {
                if (vis[x][y]) return ;
                vis[x][y] = true;
                flash.push_back(make_pair(x, y));

                for (int u = -1; u <= 1; u++)
                    for (int v = -1; v <= 1; v++)
                        if (u !=0 || v!=0)
                        {
                            if (x + u < 0 || x + u >= n || y + v < 0 || y + v >= m) 
                                continue;
                            if (pic[x + u][y + v] == '1')
                                dfs(x + u, y + v, flash);
                        }
                return ;
            };

        clog << "?" << endl;

        char to_add = 'a';
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                if (pic[i][j] == '1' && !vis[i][j])
                {
                    vector<pair<int, int> > flash;
                    dfs(i, j, flash);
                    Cluster c = build(flash);
                    if (apr.count(c) == 0)
                    {
                        //clog << "=" << endl;
                        for (int i = 0; i < 4; i++)
                        {
                            apr[c] = to_add;
#if 0
                            clog << "-" << endl;
                            for (int i = 0; i < c.first.first; i++, clog << endl)
                                for (int j = 0; j < c.first.second; j++)
                                    clog << c.second[i * c.first.second + j] ;
#endif
                            c = rotate(c);
                        }
                        c = flip(c);
                        for (int i = 0; i < 4; i++)
                        {
                            apr[c] = to_add;
#if 0
                            clog << "-" << endl;
                            for (int i = 0; i < c.first.first; i++, clog << endl)
                                for (int j = 0; j < c.first.second; j++)
                                    clog << c.second[i * c.first.second + j] ;
#endif
                            c = rotate(c);
                        }
                        to_add += 1;
                    }
                    char ID = apr[c];
                    for (auto & pr: flash)
                        pic[pr.first][pr.second] = ID;
                }
        for (auto & row: pic)
        {
            fout << row << endl;
            clog << row << endl;
        }
    }


    return 0;
}
