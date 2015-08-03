/*
ID: jchenbr1
LANG: C++11
TASK: sprime
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <cmath>
#include <functional>
using namespace std;


int main()
{
    ifstream fin("sprime.in");
    ofstream fout("sprime.out");

    // find primes , preparation
    auto findPrime = [](int n)
    {
        vector<bool> is_prime(n + 1, true);
        vector<int> prime;
        prime.reserve(n);

        for (int i = 2; i <= n; i++)
        {
            if (is_prime[i]) prime.push_back(i);

            for (auto & p : prime)
            {
                if (p * i > n) break;
                is_prime[p * i] = false;
                if (i % p == 0) break;
            }
        }

        return prime;
    };
    vector<int> prime = findPrime((int)floor(sqrt(99999999)));

    auto isPrime = [&](int num)
    {
        for (auto & p : prime)
        {
            if (p * p > num) break;
            if (num % p == 0) return false;
        }
        return true;
    };

    int n;
    while (fin>>n)
    {
        set<int> ans;
        function<void(int,int)> dfsSPrime = [&](int cur, int len)
        {
            if (!isPrime(cur)) return ;

            if (len == n)
            {
                ans.insert(cur);
            }else
                for (int nxt = (len == 0); nxt < 10; nxt ++)
                    dfsSPrime(cur * 10 + nxt, len + 1);
        };
        for (int nxt = 2; nxt < 10; nxt ++)
            dfsSPrime(nxt, 1);

        for (auto & item : ans)
        {
            fout << item << endl;
            clog << item << endl;
        }
    }

    return 0;
}
