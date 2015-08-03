/*
ID: jchenbr1
LANG: C++11
TASK: zerosum
 */
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

int main()
{
    ifstream fin("zerosum.in");
    ofstream fout("zerosum.out");

    int n;
    while (fin >> n)
    {
        string op;
        op.resize(n - 1);
        vector<string> ans;

        function<void(int, int, int, int)> dfsSum = [&](int cur_sum, int cur, int now, int lv)
        {
            if (cur == 1 && now + cur_sum == 0)
                ans.push_back(op);
            
            if (cur == 1) return ;

            op[cur - 2] = '+';
            dfsSum(cur_sum + now, cur - 1, cur - 1, 10);

            op[cur - 2] = '-';
            dfsSum(cur_sum - now, cur - 1, cur - 1, 10);

            op[cur - 2] = ' ';
            dfsSum(cur_sum , cur - 1, (cur - 1) * lv + now, lv * 10);
            return ;
        };
        dfsSum(0, n, n, 10);

        sort(begin(ans), end(ans));
        for (auto & op: ans)
        {
            clog << 1 ;
            fout << 1 ;
            for (int i = 2; i <= n; i++)
            {
                clog << op[i - 2] << i ;
                fout << op[i - 2] << i ;
            }
            clog << endl;
            fout << endl;
        }


    }

    return 0;
}
