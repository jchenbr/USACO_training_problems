/*
ID: jchenbr1
LANG: C++11
TASK: crypt1
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <memory>
#include <functional>
#include <bitset>

using namespace std;

int main(int argc, char ** argv)
{
    ifstream fin("crypt1.in");
    ofstream fout("crypt1.out");

    int n;
    while (fin >> n)
    {
        vector<int> digit(n);
        bitset<10> appear;
        for (auto & d : digit) fin >> d, appear[d] = 1;

        
        function<int(int, int)> dfsDigit = [&](int cur, int to_do)-> int
        {
            if (to_do == 0)
            {
                int a = cur / 100, b = cur % 100;
                int c = a * (b / 10), d = a * (b % 10);
                int e = c * 10  + d;

                if (c < 100 || c > 999) return 0;
                if (d < 100 || d > 999) return 0;
                if (e < 1000 || e > 9999) return 0;

                for (int idx = 0; idx < 3; idx ++)
                {
                    bitset<10> app(1 << (c % 10) | 1 << (d % 10) | 1 << (e % 10));
                    app &= ~appear;
                    if (app.any()) return 0;
                    c /= 10, d /= 10, e /= 10;     
                }
                //clog << "dfs_state : " << to_do << ", "<< cur << endl;
                //clog << c << ", " << d << ", " << e << endl; 
                if (appear.test(e))
                    return 1;
                else
                    return 0;
            }else
            {
                int ret = 0;
                for (auto d : digit)
                    ret += dfsDigit(cur * 10 + d, to_do - 1);
                return ret;
            }
        };

        fout << dfsDigit(0, 5) << endl;
        clog << dfsDigit(0, 5) << endl;
    }

    return 0;
}
