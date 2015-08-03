/*
ID: jchenbr
LANG: C++11
TASK: shopping
 */
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

int main()
{
    ifstream fin("shopping.in");
    ofstream fout("shopping.out");

    int n, m;
    while (fin >> m)
    {
        vector<pair<vector<pair<int, int> >, int>> offer(m);
        map<int, int> code2item;
        int iid = 0;


        for (auto & f: offer)
        {
            int n_item;
            fin >> n_item;
            f.first.resize(n_item);
            for (auto & pr: f.first)
            {
               fin >> pr.first >> pr.second;
               if (code2item.count(pr.first) == 0)
                   code2item[pr.first] = iid++;
               pr.first = code2item[pr.first];
            }
            fin >> f.second;
        }

        fin >> n;
        vector<int> lim(n);
        vector<int> price(n);
        int c, p, k;
        for (int i = 0; i < n; i++)
        {
            fin >> c >> k >> p;
            if (code2item.count(c) == 0)
                code2item[c] = iid++;
            c = code2item[c];
            lim[c] = k;
            price[c] = p;
        }

        auto _func_state_to_id = [&](const vector<int> & a)
        {
            int ret = 0;
            for (size_t idx = 0; idx < a.size(); idx++)
            {
                ret = ret * (lim[idx] + 1) + a[idx];
            }
            return ret;
        };

        auto _func_id_to_state = [&]( int state)
        {
            vector<int> a(n);
            for (int idx = n - 1; idx >= 0; idx--)
            {
                a[idx] = state % (lim[idx] + 1);
                state /= lim[idx] + 1; 
            } 
            return a;
        };

        int S = _func_state_to_id(lim) + 1;
        clog << " S = " << S << endl;

        vector<int> opt(S , 0);

        for (int state = 0; state < S; state++)
        {
            vector<int> a = _func_id_to_state(state);
            //for (auto & it: a) clog << it << " "; clog << endl;
            for (int idx = 0; idx < n; idx++)
                opt[state] += a[idx] * price[idx];
        }

        clog << "? " << endl;

        for (int state = 0; state < S; state++)
        {
            vector<int> a = _func_id_to_state(state);
            for (auto & f: offer)
            {
                vector<int> b(a);
                bool flag = true;

                for (auto & pr: f.first)
                {
                    b[pr.first] += pr.second;
                    if (b[pr.first] > lim[pr.first])
                        flag = false;
                }

                if (flag)
                {
                    int nxt = _func_state_to_id(b);
                    if (opt[state] + f.second < opt[nxt])
                        opt[nxt] = opt[state] + f.second; 
                }
            }
        }

        fout << opt[S - 1] << endl;
        clog << opt[S - 1] << endl;
    }

    return 0;
}
