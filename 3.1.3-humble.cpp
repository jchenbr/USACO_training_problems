/*
ID: jchenbr1
LANG: C++11
TASK: humble
 */
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

typedef long long LL;

int main()
{
    ifstream fin("humble.in");
    ofstream fout("humble.out");

    int n, m;
    while (fin >> n >> m)
    {
        vector<LL> prime(n);
        for (auto & p : prime) fin >> p;
        sort(begin(prime), end(prime));

        vector<LL> now(m + 1);
        vector<int> last(m + 1);
        set<pair<LL, int> > nxt_id;

        int u = 0, val = 1;
        now[0] = val;
        last[0] = 0;
        nxt_id.insert(make_pair(prime[0] * val, u));

        for (int i = 1; i <= m; i++)
        {
            u = nxt_id.begin() -> second;

            now[i] = nxt_id.begin() -> first;
            last[i] = last[u];

            // 1.
            nxt_id.erase(begin(nxt_id));
            last[u] += 1;
            if (last[u] < n)
                nxt_id.insert(make_pair(prime[last[u]] * now[u], u));
            // 2.
            nxt_id.insert(make_pair(prime[last[i]] * now[i], i));
        }
        //for (auto & item: now) clog << item << " " ; clog << endl ;

        fout << now[m] << endl;
        clog << now[m] << endl;
    }

    return 0;
}
