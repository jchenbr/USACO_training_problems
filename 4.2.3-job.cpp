/*
ID: jchenbr1
LANG: C++11
TASK: job
 */
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    ifstream fin("job.in");
    ofstream fout("job.out");

    int n, m, k;
    while (fin >> k >> n >> m)
    {
        vector<int> cost_a(n);
        for (auto & cost: cost_a) fin >> cost;

        vector<int> cost_b(m);
        for (auto & cost: cost_b) fin >> cost;

        vector<int> state(n, 0);

        vector<int> mid(k);
        const int inf = 1000000000;
        int ans_a = inf;
        for (int i = 0; i < k; i++)
        {
            int opt = 0, fin_time = inf;
            for (int j = 0; j < n; j++)
                if (state[j] + cost_a[j] < fin_time)
                {
                    fin_time = state[j] + cost_a[j];
                    opt = j;
                }
            state[opt] = fin_time;
            mid[i] = fin_time;
        }
        sort(state.begin(), state.end());
        ans_a = state.back();
        
        //for (auto & item : mid) clog << " " << item ; clog << endl;

        auto check = [&](int fin_time)
        {
            vector<int> state_b(m, fin_time);

            for (int i = k - 1; i >= 0; i --)
            {
                int s = mid[i], opt = 0, start_time = -1;
                for (int j = 0; j < m; j++)
                    if (state_b[j] - cost_b[j] >= s)
                    {
                        if (state_b[j] - cost_b[j] > start_time)
                        {
                            start_time = state_b[j] - cost_b[j];
                            opt = j;
                        }
                    }
                if (start_time < 0) return false;
                state_b[opt] = start_time;
            }
            return true;
        };

        int l = ans_a, r = 50000, md;
        while (l < r)
        {
            md = (l + r) >> 1;
            if (check(md))
                r = md;
            else
                l = md + 1;
        } 
        fout << ans_a << " " << l << endl;
        clog << ans_a << " " << l << endl;

    }


    return 0;
}
