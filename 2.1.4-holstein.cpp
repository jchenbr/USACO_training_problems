/*
ID: jchenbr
LANG: C++11
TASK: holstein
 */

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <queue>
#include <functional>

using namespace std;

int main()
{
    ifstream fin("holstein.in");
    ofstream fout("holstein.out");

    int n, m;
    while (fin >> n)
    {
        vector<int> need(n);
        for (auto & item: need) fin >> item;

        fin >> m;
        vector<vector<int> > scroop(m, vector<int>(n));
        for (auto & s: scroop)
            for (auto & item: s) fin >> item;

        for (auto & s: scroop)
        { 
            for (auto & item: s) clog << item << ", ";
            clog << endl;
        }

        int ans = m , mask = (1 << m) - 1;

        vector<int> feed(n, 0);

        function<void(int,int,int)> dfsFeed  = [&](int state, int cur, int lv)
        {
            bool flag = true;

            for (size_t idx = 0; flag && idx < n; idx ++ ) 
                flag = feed[idx] >= need[idx];

            if (flag) 
            {
                ans = lv, mask = state;

                clog << "[]"<< ans << ", " << state << ", " << cur << endl;
                for (auto & f : feed) clog << f << " ";
                clog << endl;
            }

            for (int i = cur; i < m; i++)
                if (lv + 1 < ans) 
                {
                    for (size_t idx = 0; idx < n; idx ++ ) 
                        feed[idx] += scroop[i][idx];

                    //clog << "go, " << state << ", to_add = " << i << endl; 
                    dfsFeed(state | (1 << i), i + 1, lv + 1);

                    for (size_t idx = 0; idx < n; idx ++ )
                        feed[idx] -= scroop[i][idx];
                }
        };

        dfsFeed(0, 0, 0);

        fout << ans ;
        for (int i = 0; i < m; i++)
            if (mask >> i & 1) fout << " " << i + 1;
        fout << endl;

        clog << ans ;
        for (int i = 0; i < m; i++)
            if (mask >> i & 1) clog << " " << i + 1;
        clog << endl;
    }

    return 0;
}
