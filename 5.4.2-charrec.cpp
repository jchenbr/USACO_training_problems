/*
ID: jchenbr
LANG: C++11
TASK: charrec
 */
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int main()
{
    ifstream din("font.in");
    ifstream fin("charrec.in");
    ofstream fout("charrec.out");

    const int inf = 1000000000 + 5;
    int n, m;
    din >> m;
    string b[m + 1];
    for (int i = 1; i <= m; i++)
        din >> b[i];

    auto cmp = [&](string & a, string & b)
    {
        int ret = 0;
        for (int i = 0; i < 20; i++)
            ret += a[i] != b[i];
        //clog << a << ", " << b << ", " << ret << endl;
        return ret;
    };

    fin >> n;
    int cost[n + 1][28][21];

    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= 27; j++)
            for (int k = 0; k <= 20; k++)
            cost[i][j][k] = inf;

    for (int i = 1; i <= n; i++)
    {
        string str;
        fin >> str;

        for (int j = 0; j < m; j++)
            cost[i][j / 20 + 1][j % 20 + 1] = cmp(str, b[j + 1]);
    }

    //clog << " n = " << n << ", m = " << m << endl;
    //for (int i = 0; i <= n; i++, clog << endl)
    //    for (int j = 0; j <= m; j++) clog << cost[i][j] << "\t";

    int f[n + 1][28][21][3];

    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= 27; j++)
            for (int k = 0; k <= 20; k++)
                for (int l = 0; l < 3; l++)
                    f[i][j][k][l] = inf;

    for (int j = 1; j <= 27; j++)
        f[0][j][0][0] = 0;

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= 27; j++)
        {
            for (int k = 1; k <= 20; k++)
            {
                f[i][j][k][0] = f[i - 1][j][k - 1][0] + cost[i][j][k];

                f[i][j][k][1] = min(f[i][j][k - 1][0], f[i - 1][j][k - 1][1] + cost[i][j][k]);

                f[i][j][k][2] = min(f[i - 1][j][k][0], f[i - 1][j][k - 1][2] + cost[i][j][k]);
            }

            for (int J = 1; J <= 27; J++)
                for (int l = 0; l < 3; l++)
                    f[i][J][0][0] = min(f[i][J][0][0], f[i][j][20][l]);
        }

    string str;
    int i = n;
    while (i > 0)
    {
        int ch_j = -1, ch_k = -1, opt = inf;
        for (int j = 1; j <= 27; j++)
        {
            for (int k = 0; k < 3; k++)
                if (opt > f[i][j][20][k])
                {
                    opt = f[i][j][20][k];
                    ch_j = j;
                    ch_k = k;
                }
           clog << "(" << j << ", " << f[i][j][20][0] << ", " << f[i][j][20][1] << ", " << f[i][j][20][2] << ")"<< endl;
        }

        if (ch_j > 1) 
            str = (char)('a' + ch_j - 2) + str;
        else if (ch_j == 1)
            str = ' ' + str; 
        clog << "opt = " << opt <<", i = " << i << ", ch_j = " << ch_j << ", ch_k = " << ch_k << ", " << str << endl;
        i -= 20 - (ch_k == 1) + (ch_k == 2); 
    }

    fout << str << endl;
    clog << str << endl;


    return 0;
}
