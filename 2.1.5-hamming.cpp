/*
ID: jchenbr1
LANG: C++11
TASK: hamming
 */

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <functional>
using namespace std;

int main()
{
    ifstream fin("hamming.in");
    ofstream fout("hamming.out");

    int n, len, D;
    while (fin >> n >> len >> D)
    {
        auto getDistance = [&](int a, int b)
        {
            int c = a ^ b;
            int ret = 0;
            while (c) 
            {
                ret += 1;
                c -= (c & -c) ;
            }
            //clog << "(" << a << ", " << b << ", " << c << ") = " << ret << endl;
            return ret;
        };
        bool flag = false;
        vector<int> ans(n);
        function<void(int, int)> dfsCode = [&](int lv, int cur)
        {
            //clog << "lv = " << lv << ", cur = " << cur << endl; 
            if (lv == n) 
                flag = true;
            for (int i = cur; !flag && i < len; i++)
            {   
                bool cap = true;
                for (int j = lv - 1; cap && j >= 0; j--)
                    cap = getDistance(i, ans[j]) >= D;
                if (cap)
                    ans[lv] = i, dfsCode(lv + 1, i + 1);
            }
        };

        len = 1 << len;
        dfsCode(0, 0);
        for (int i = 0; i < n; i++)
        {
            if ( i)
            {
                if (i % 10) 
                    fout << " ", clog << " ";
                else
                    fout << endl, clog << endl;
            }
            fout << ans[i];
            clog << ans[i];
        }
        fout << endl;
        clog << endl;
    }

    return 0;
}
