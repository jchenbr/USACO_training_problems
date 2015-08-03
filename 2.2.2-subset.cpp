/*
ID: jchenbr1
LANG: C++11
TASK: subset
 */
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main()
{
    ifstream fin("subset.in");
    ofstream fout("subset.out");

    int n;
    while (fin >> n)
    {
        vector<long long> count((n + 1) * n, 0);

        count[0] = 1;
        int lim = (1 + n) * n / 2;

        for (int i = 1; i<= n; i++)
        {
            for (int sum = lim - i; sum >=0; sum--)
                count[sum + i] += count[sum];
        }

        long long ans = count[(1 + n) * n / 4] / 2;

        if ((1 + n) * n % 4 ==0)
        {
            fout << ans << endl;
            clog << ans << endl;
        }else
            fout << "0" << endl;
    }

    return 0;
}
