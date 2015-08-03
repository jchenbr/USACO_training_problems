/*
ID: jchenbr1
LANG: C++11
TASK: fact4
 */
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

int main()
{
    ifstream fin("fact4.in");
    ofstream fout("fact4.out");

    auto getPrime = [&](int n)
    {
        vector<bool> is_prime(n + 1, true);
        vector<int> prime;
        prime.reserve(n + 1);
        for (int i = 2; i <= n; i++)
        {
            if (is_prime[i]) prime.push_back(i);
            for (auto & p : prime)
            {
                if (i * p > n) break; 
                is_prime[i * p] = false;
                if (i % p == 0) break;
            }
        }  
        return prime;
    };

    int n, N = 4220;
    vector<int> prime = getPrime(N);

    while (fin >> n)
    {
        map<int, int> count;

        for (auto & p: prime) count[p] = 0;

        for (int i = 2; i <= n; i++)
        {
            int j = i;
            for (auto & p : prime)
            {
                if (p * p > j) break;
                while (j % p == 0) 
                {
                    count[p] += 1, j/=p;
                }
            }
            if (j > 1) count[j] += 1;
        }

        int nz = min(count[2], count[5]);
        count[2] -= nz;
        count[5] -= nz;
        int ans = 1;
        for (auto & pr: count)
        {
            //if (pr.first < 50) clog << pr.first << ", " << pr.second << endl;
            for (int i = 0; i < pr.second; i++)
            {   
                //clog << "-" << pr.first << endl;
                ans *= pr.first, ans %= 10;
            }
        }
        fout << ans << endl;
        clog << ans << endl;
    }

    return 0;
}
