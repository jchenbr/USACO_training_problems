/*
ID: jchenbr1
LANG: C++11
TASK: vans
 */
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <string>
using namespace std;
typedef long long LL;

struct BigNum
{
    int data[1000];
    int len;
    BigNum()
    {
        len = 1;
        memset(data, 0, sizeof(data));
    }

    int & operator[](int idx)
    {
        if (idx < len)
            return data[idx];
        else
        {
            data[idx] = 0;
            return data[idx];
        }
    }

    void set(int num)
    {
        len = 0;
        do
        {
            data[len++] = num % 10;
            num /= 10;
        }while (num != 0);
    }

    void operator += (BigNum & u)
    {
        int Len = max(len, u.len);
        int x = 0;
        for (int i = 0; i < Len; i++)
        {
            x = (*this)[i] + u[i] + x;
            data[i] = x % 10;
            x /= 10;
        }
        if (x)
            data[Len++] = x;
        len = Len;
    }

    void operator = (int num)
    {
        set(num);
    }

    string to_string()
    {
        string ret ;
        //clog << "len = " << len << endl;
        for (int i = len - 1; i >=0; i--)
        {
            //clog << data[i];
            ret += (char)data[i] + '0';
        }

        //clog << endl;
        return ret;
    }
};


int main()
{
    ifstream fin("vans.in");
    ofstream fout("vans.out");


    int n = 1000;


    int to[6][6] = 
    {
        0, 0, 0, 1, 1, 0,
        0, 0, 0, 1, 0, 0,
        0, 0, 0, 1, 1, 0,
        1, 1, 1, 0, 0, 1,
        0, 0, 0, 1, 1, 0,
        1, 0, 1, 0, 0, 1
    };


    while (fin >> n)
    {
        BigNum f[2][6];
        f[1][5] = 1;
        f[1][3] = 1;

        for (int i = 2; i < n; i++)
        {
            for (int j = 0; j < 6; j++)
            {
                f[i & 1][j] = 0;

                for (int k = 0; k < 6; k++)
                    if (to[j][k])
                    f[i & 1][j] += f[~i & 1][k];
            }
            //clog << "? i = " << i << endl;
        }
        //clog << "!" << endl;



        BigNum ans = f[(n - 1) & 1][4];
        ans += f[(n - 1) & 1][3];

        BigNum tmp = ans;
        ans += tmp;
        
        //clog << "!!" << endl;

        clog << ans.to_string() << endl;
        fout << ans.to_string() << endl;
    }

    return 0;
}
