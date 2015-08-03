/*
ID: jchenbr1
LANG: C++11
TASK: pprime
 */

#include <iostream>
#include <cstdio>
#include <fstream>
#include <vector>
#include <set>
#include <cstdlib>
#include <cmath>
#include <functional>

using namespace std;

int main()
{
    ifstream fin("pprime.in");
    ofstream fout("pprime.out");

    int a, b;
    while (fin >> a >> b)
    {

        int len = 0, tmp = b;
        while (tmp > 0) len += 1, tmp /= 10;
        set<int> ans;
        clog << a << ", " << b << ", " << len << endl;

        auto findPrime = [&](int n)
        {
            vector<int> is_prime(n + 1, true);
            vector<int> prime;
            prime.reserve(n);
            for (int i = 2; i <= n; i++)
            {
                if (is_prime[i]) prime.push_back(i);

                for (auto & p: prime)
                {
                    if (i * p > n) break;
                    is_prime[i * p] = false;
                    if (i % p == 0) break;
                }
            }
            return prime;
        };

        clog << "?" << floor(sqrt(b)) << endl;
        vector<int> prime = findPrime((int)floor(sqrt(b)));
        for (auto p : prime)
            clog << p << endl;
        clog << "end prime" << endl;

        auto isPrime = [&](int num)
        {
            for (auto p : prime)
            {
                if (p * p > num) break;
                if (num % p == 0) return false; 
            }
            return true;
        };

        auto reverseNum = [&](int num)
        {
            int ret = 0;
            while (num) ret = ret * 10 + num % 10, num /= 10;
            return ret;
        };
        
        function<void(int,int)> findPPrime = [&](int cur, int length) -> void
        {
            int pos = 1;
            for (int i = 0; i < length; i++) pos *= 10;
            int val = reverseNum(cur) + cur * pos;
            if (val >= a && val <= b && isPrime(val))
                ans.insert(val);

            if ((length * 2 + 1) <= len)
            {
                for (int mid = 0; mid < 10; mid ++)
                {
                    val = reverseNum(cur) + mid * pos + cur * pos * 10;
                    if (val >= a  && val <= b && isPrime(val))
                        ans.insert(val);
                }
            } 

            if (length + 1 <= (len >> 1))
            {
                for (int nxt = (length == 0); nxt < 10; nxt++)
                    findPPrime(cur * 10 + nxt, length + 1);
            }
        };
        
        findPPrime(0, 0);

        for (auto & item : ans)
        {
            fout << item << endl;
            clog << item << endl;
        }
    }

    return 0;
}
