/*
ID: jchenbr
LANG: C++11
TASK: picture
 */
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <functional>
#include <map>
using namespace std;

#define mp(x, y) (make_pair((x), (y)))

struct Node
{
    int l, r, val, top;
};

int main()
{
    ifstream fin("picture.in");
    ofstream fout("picture.out");

    int n, ans = 0;
    fin >> n;
    vector<pair<pair<int, int>, pair<int, int> > > a(n);

    auto solve = [&](vector< pair< pair<int, int>, pair<int,int> > > & a)
    {
        vector<int> ps;
        ps.reserve(n << 1);

        for (auto & item : a)
        {
            ps.push_back(item.second.first);
            ps.push_back(item.second.second);
        }

        sort(ps.begin(), ps.end());
        int m = 0;
        map <int, int> id_ps;
        vector<int> ps_id;

        for (int i = 0; i < (int)ps.size(); i++)
            if (i == 0 || ps[i] != ps[i - 1])
            {
                id_ps[ps[i]] = m++;
                ps_id.push_back(ps[i]);
            }

        vector<int> count(m, 0);

        vector<pair<pair<int, int>, pair<int, int> > > query;
        query.reserve(n << 1); 

        for (auto & item : a)
        {
            query.push_back(mp(mp(item.first.first, -1),mp(id_ps[item.second.first], id_ps[item.second.second])));
            query.push_back(mp(mp(item.first.second, 1),mp(id_ps[item.second.first], id_ps[item.second.second])));
        }
        sort(query.begin(), query.end());

        for (auto & q : query)
        {
            for (int i = q.second.first; i < q.second.second; i++)
            {
                if (count[i] == 0)
                    ans += ps_id[i + 1] - ps_id[i];

                count[i] -= q.first.second;

                if (count[i] == 0)
                    ans += ps_id[i + 1] - ps_id[i];
            }
        }
    };

    for (auto & item: a)
    {
        fin >> item.first.first >> item.second.first;
        fin >> item.first.second >> item.second.second;
    }

    solve(a);

    for (auto & item: a)
        swap(item.first, item.second);

    solve(a);

    clog << ans << endl;
    fout << ans << endl;

    return 0;
}
