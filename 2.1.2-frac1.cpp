/*
ID: jchenbr1
LANG: C++11
TASK: frac1
 */
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>
#include <functional>

using namespace std;

int main()
{
    ifstream fin("frac1.in");
    ofstream fout("frac1.out");


    int n;
#if 0
    while (fin >> n)
    {
        vector<pair<double, pair<int, int> > > ans;
        auto gcd = [](int x, int y)
        {
            while (y) x%=y, swap(x, y);
            return x;
        };
        ans.reserve((n + 1) * (n + 1));

        for (int y = 1; y <= n; y++)
            for (int x = 1; x <= y; x++)
            {
                if (gcd(x, y) != 1) continue;
                ans.push_back(make_pair(x/(double)y, make_pair(x , y )));
            }
       
        sort(begin(ans), end(ans));


        fout << "0/1" << endl;
        //clog << "0/1" << endl;
        for (size_t idx = 0; idx < ans.size(); idx ++ )
        {
            if (idx && (ans[idx].second == ans[idx - 1].second)) continue;
            fout << ans[idx].second.first << "/" << ans[idx].second.second << endl;
            //clog << ans[idx].second.first << "/" << ans[idx].second.second << endl;
        }
    }
#endif
    while (fin >> n)
    {
        function<void(int,int,int,int,int)> print_frac = [&](int a, int b, int c, int d, int n) -> void
        {
            if (b + d <= n)
            {
                print_frac(a, b, a + c, b + d, n);
                fout << a + c << "/" << b + d << endl;
                //clog << a + c << "/" << b + d << endl;
                print_frac(a + c, b + d, c, d, n);
            }
        };

        fout << "0/1" << endl;
        //clog << "0/1" << endl;
        print_frac(0, 1, 1, 1, n);
        fout << "1/1" << endl;
        //clog << "1/1" << endl;
    }

    return 0;
}

