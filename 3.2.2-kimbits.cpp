/*
ID: jchenbr
LANG: C++11
TASK: kimbits
 */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int main()
{
    ifstream fin("kimbits.in");
    ofstream fout("kimbits.out");

    long long f[32][32][2] = {}, g[32][32][2] = {};

    f[0][0][0] = 1;

    for (int i = 1; i < 32; i++)
        for (int j = 0; j < 32; j++)
        {
            f[i][j][0] = f[i - 1][j][1] + f[i - 1][j][0];
            if (j)
                f[i][j][1] = f[i - 1][j - 1][1] + f[i - 1][j - 1][0];

            g[i][j][0] = f[i][j][0];
            g[i][j][1] = f[i][j][0];
            if (j)
            {
                g[i][j][0] += g[i][j - 1][0];
                g[i][j][1] += g[i][j - 1][1];
            }
        }

    int n, m;
    long long I;
    clog << "??" << endl;
    while (fin >> n >> m >> I)
    {
        clog << "I = " << I << endl;
        string str ;
        while (n != 0)
        {
            //clog << f[n][m][0] << ", " << f[n][m][1] << endl;
            if (I <= g[n][m][0])
            {
                str += "0";
                n -= 1;
            }else
            {
                str += "1";

                I -= g[n][m][0];
                n -= 1;
                m -= 1;
            }
            //clog << "I = " << I << endl;
        }
        fout << str << endl;
        clog << str << endl;
    }
    return 0;
}
