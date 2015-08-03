/*
ID: jchenbr1
LANG: C++11
TASK: buylow
 */
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <set>
#include <string>
#include <cstring>
using namespace std;

struct BigNum
{
    int a[100], n;

    BigNum(int num)
    {
        memset(a, 0, sizeof(a));
        n = 0;
        while (num) a[n++] = num % 10, num/= 10;
    }

    void clone(const BigNum & num)
    {
        n = num.n;
        memcpy(a, num.a, sizeof(a));
    }

    void add(const BigNum & num)
    {
        
        int x = 0;
        n = max(n , num.n);
        for (int i = 0; i < n; i++)
        {
            x = a[i] + num.a[i] + x; 
            a[i] = x % 10;
            x /= 10;
        }
        if (x) a[n++] = x;
    }

    string output()
    {
        string ret;
        for (int i = n - 1; i >= 0; i--)
            ret += to_string(a[i]);
        if (ret.size() == 0) ret += "0";
        return ret;
    }
};

int main()
{
    ifstream fin("buylow.in");
    ofstream fout("buylow.out");

    int n;
    while (fin >> n)
    {
        vector<int> a(n);
        for (auto & item : a) fin >> item;
        a.push_back(0);

        n += 1;
        vector<int> f(n , 1);
        vector<BigNum> g(n, 1);

        for (int i = 1; i < n; i++)
        {
            for (int j = i - 1; j >= 0; j--)
            if (a[j] > a[i] && f[j] + 1 > f[i])
            {
                f[i] = f[j] + 1;
            }


            if (f[i]!=1)
                g[i] = BigNum(0);
            else
                continue;
            //if (i < 100) clog << " == " << g[i].output() << endl;
            set<int> last;
            //if (i < 10) clog << "==" << i << endl;
            for (int j = i - 1; j >= 0; j--)
                if (a[j] > a[i] && f[j] + 1 == f[i])
                {
                    if (last.count(a[j]) > 0) continue;
                    last.insert(a[j]);
                    //if (i < 20) clog << "\t" << "j = " << j <<", "<< g[i].output() << ", " << g[j].output() <<endl;
                    g[i].add(g[j]);
                    //if (i < 20) clog << "\t" << g[i].output() << ", len = "<< g[i].n <<endl;
                }
            //if (i < 100) clog << "\t>> " << i << " - " << g[i].output() << endl;
        }

        clog << f[n - 1] - 1 << " " << g[n - 1].output() << endl;
        fout << f[n - 1] - 1 << " " << g[n - 1].output() << endl;
    }

    return 0;
}

