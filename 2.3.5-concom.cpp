/*
ID: jchenbr1
LANG: C++11
TASK: concom
 */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <functional>
#include <algorithm>
using namespace std;

int main()
{
    ifstream fin("concom.in");
    ofstream fout("concom.out");

    int n;
    while (fin >> n)
    {
        vector<vector<int> > stock(101, vector<int>(101, 0));
        while (n --)
        {
            int u, v, c;
            fin >> u >> v >> c;
            stock[u][v] = c;
        }
        vector<vector<int> > sum(stock);
        vector<vector<bool> > con(101, vector<bool>(101, false));
        for (int i = 1; i<= 100; i++) con[i][i] = true;

        vector<pair<int,int> > ans;
        
        function<void(int, int)> control = [&](int u, int v)
        {
            if (con[u][v] || sum[u][v] <= 50) return ;
            con[u][v] = true;
            ans.push_back(make_pair(u, v));

            for (int i = 1; i <= 100; i++)
            {
                sum[u][i] += stock[v][i];
                control(u, i);
            }
        };

        for ( int i = 1; i <= 100; i++)
            for (int j = 1; j <= 100; j++)
                control(i, j);
        sort(begin(ans), end(ans));

        for (auto & p : ans) 
        {
            //clog << p.first << " " << p.second << endl;
            fout << p.first << " " << p.second << endl;
        }
    }

    return 0;
}
