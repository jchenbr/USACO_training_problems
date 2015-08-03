/*
ID: jchenbr1
LANG: C++11
TASK: fence8
 */
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

int main()
{
    ifstream fin("fence8.in");
    ofstream fout("fence8.out");

    int n, m;
    while (fin >> n)
    {
        vector<int> bucket(n);
        for (auto & one : bucket) fin >> one;

        fin >> m;
        vector<int> good(m);
        for (auto & one : good) fin >> one;

        sort(good.begin(), good.end());
        sort(bucket.begin(), bucket.end());
        int remain_sum = 0, allowed_remain = 0;
        
        function<bool(int, int)> dfs = [&](int idx, int beg)
        {
            //clog << idx << "/"  << endl;
            if (idx < 0) return true;

            if (!(idx + 1 < m && good[idx + 1] == good[idx]))
                beg = 0;
            if (remain_sum > allowed_remain) return false;

            for (int i = beg; i < n; i++)
            {
                if (bucket[i] < good[idx]) continue;

                bucket[i] -= good[idx];
                if (bucket[i] < good[0])
                    remain_sum += bucket[i];

                if (dfs(idx - 1, i)) 
                {
                    bucket[i] += good[idx];
                    return true;
                }

                if (bucket[i] < good[0])
                    remain_sum -= bucket[i];
                bucket[i] += good[idx];
            }
            return false;
        };

        for (int i = 0; i < m; i++) clog << good[i] << " "; clog << endl;
        

        int ans = 0;
        for (int i = 1; i <= m; i++)
        {
            //clog << "i = " << i << endl;

            allowed_remain = remain_sum = 0;

            for (int j = 0; j < n; j ++) allowed_remain += bucket[j];
            for (int j = 0; j < i; j++) allowed_remain -= good[j];

            if (dfs(i - 1, 0))
                ans = i;
            else
                break;
        }
        fout << ans << endl;
        clog << ans << endl;
    }

    return 0;
}
