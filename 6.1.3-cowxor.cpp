/*
ID: jchenbr1
LANG: C++11
TASK: cowxor
 */
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <unordered_map>
using namespace std;

inline bool test(int x, int idx)
{
    return (x >> idx) & 1;
}

int main()
{
    ifstream fin("cowxor.in");
    ofstream fout("cowxor.out");

    int n, m = 21;
    while (fin >> n)
    {
        vector<int> a(n + 1);
        vector<int> f(n + 1, 0);

        for (int i = 1; i <= n; i++)
        {
            fin >> a[i];
            f[i] = f[i - 1] ^ a[i];
        }

        vector<int> apr;
        apr.reserve(1 << m);
        int xorsum = 0;
        for (int j = m - 1; j >= 0; j--)
        {
            apr.clear();
            apr.resize(1 << (m - j), -1);

            int tmp = xorsum << 1 | 1;

            bool flag = false;

            for (int i = 0; i <= n; i++)
            {
                if (apr[(f[i] >> j) ^ tmp] >= 0)
                    flag = true;
                apr[f[i] >> j] = i;
            }
            xorsum <<= 1;
            xorsum |= flag;
        }


        apr.clear();
        apr.resize(1 << m, -1);
        pair<int, int> ans(n + 1, n + 1);

        for (int i = 0; i <= n; i++)
        {
            if (apr[f[i] ^ xorsum] >= 0)
            {
                //clog << "i = " << i << ", head = " << apr[f[i] ^ xorsum] << endl;
                pair<int, int> tmp(i, i - apr[f[i] ^ xorsum]);
                if (tmp < ans) ans = tmp;
            }
            apr[f[i]] = i;
        }

        fout << xorsum << " " << ans.first - ans.second + 1 << " " << ans.first << endl;
        clog << xorsum << " " << ans.first - ans.second + 1 << " " << ans.first << endl;
    }

    return 0;
}
