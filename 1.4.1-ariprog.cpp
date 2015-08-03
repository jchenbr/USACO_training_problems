/*
ID: jchenbr1
LANG: C++11
TASK: ariprog
 */

#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>

using namespace std;

int main()
{
    ifstream fin("ariprog.in");
    ofstream fout("ariprog.out");

    int n, m;
    fin >> n >> m;
    {
#if 0 
        auto findPrimes = [] (int m)
        {
            vector<int> primes;
            vector<bool> is_prime(m + 1, true);
            for (int idx = 2; idx <= m; idx++)
            {
                if (is_prime[idx])
                    primes.push_back(idx);
                for (auto & p: primes)
                    if (p * idx <= m)
                    {
                        is_prime[p * idx] = true;
                        if ( idx % p == 0) break;
                    } else break;
            }
            return primes;
        };
#endif
        //vector<int> primes = findPrimes(m);
        vector<int> bisquare;
        vector<bool> is_bisquare( (m * m << 1) + 1, false);
        bisquare.reserve(m * m << 1);

        for (int u = 0; u <= m; u ++)
            for (int v = u; v <= m; v++)
            {
                if (is_bisquare[u * u + v * v]) continue;
                bisquare.push_back(u * u + v * v);
                is_bisquare[u * u + v * v] = true;
            }
        sort(begin(bisquare), end(bisquare));

        vector<pair<int, int> > ans;

        for (auto pBeg = begin(bisquare); pBeg != end(bisquare); pBeg ++)
            for (auto pTail = prev(end(bisquare)); pTail != pBeg ; pTail --)
            {
                if ((*pTail - *pBeg)%(n- 1) > 0) continue;
                int step = (*pTail - *pBeg)/(n - 1), beg = *pBeg;
                bool flag = true;
                for (int i = 1; i < n; i++)
                    if (is_bisquare[beg + step * i] == 0) 
                    {
                        flag = false;
                        break;
                    }

                if (flag)
                {
                    ans.push_back(make_pair(step, beg));
                }
            }

        sort(begin(ans), end(ans));
        if (ans.empty())
        {
            fout << "NONE" << endl;
            clog << "NONE" << endl;
        }else
            for (auto & pr: ans)
            {
                fout << pr.second << " " << pr.first << endl;
                clog << pr.second << " " << pr.first << endl;
            }
        clog << "WTF?!" << endl;
    }

    return 0;
}
