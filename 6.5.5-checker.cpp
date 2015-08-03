/*
ID: jchenbr1
LANG: C++11
TASK: checker
 */

/* Oh my, I achieved my high school dream. Witness! lol */
#include <iostream>
#include <fstream>
#include <vector>
#include <functional>
using namespace std;

int main()
{
    ifstream fin("checker.in");
    ofstream fout("checker.out");

    int n;
    while (fin >> n)
    {
        vector<int> crt;
        crt.reserve(n);
        vector<vector<int> > ans_list;
        int ans = 0;

        function<void(int, int, int)> dfs = [&](int l, int u, int r)
        {
            if (u + 1 == 1 << n)
            {
                ans += 1;
                if (ans <= 3)
                    ans_list.push_back(crt);
                return ;
            }

            int msk = (~(l | r | u) ) & ((1 << n) - 1);
            for (int val = msk & (-msk); msk; val = msk & (-msk))
            {
                msk ^= val;
                crt.push_back(val);
                dfs((l | val) << 1, u | val, (r | val) >> 1);
                crt.pop_back();
            }
        };

        dfs(0, 0, 0);

        for (auto & crt: ans_list)
        {
            for (auto it = crt.begin(); it != crt.end(); it++)
            {
                if (it != crt.begin())
                {
                    fout << " ";
                    clog << " ";
                }
                int val = *it;
                for (int i = 0; ; i += 1)
                    if (val == 1 << i)
                    {
                        val = i + 1;
                        break;
                    }
                fout << val;
                clog << val; 
            }
            clog << endl;
            fout << endl;
        }

        clog << ans << endl;
        fout << ans << endl;
    }

    return 0;
}
