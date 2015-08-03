/*
ID: jchenbr1
LANG: C++11
TASK: calfflac
 */
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <cctype>
#include <cstring>
using namespace std;

int main()
{
    ifstream fin("calfflac.in");
    ofstream fout("calfflac.out");

    
    string str, a;
    str.resize(20000 + 5);
    a.resize(20000 + 5);
    vector<int> pos(20000 + 5, 0);

    int m = 0, n = 0;
    char ch;

    while ((ch = fin.get()) != EOF)
    {
        if (isalpha(ch))
        {
            a[n] = tolower(ch);
            pos[n++] = m;
        }
        str[m ++ ] = ch;
    }

    //str.resize(m);
    //clog << "str = " << str << endl;
    //a.resize(n);
    //clog << "a = " << a << endl;


    vector<int> f(n, 1);
    for (int r = 1; r < n; r++)
    {
        int l = r - f[r - 1] - 1;
        if (l >= 0 && a[l] == a[r])
        {
            f[r] = f[r - 1] + 2;
        }
        else
        {
            for (int i = l + 1; i <= r; i++)
                if (a[i] == a[r])
                {
                    bool flag = true;
                    for (int x = i, y = r; x < y; x++, y--)
                        if (a[x] != a[y])
                        {
                            flag = false;
                            break;
                        }
                    if (flag)
                    {
                        f[r] = r - i + 1;
                        break;
                    }
                }
        }
    }

    int ans = 0, beg = -1, last = -1;
    for (int i = 0; i < n; i++)
    {
        //clog << f[i] << " ";
        if (f[i] > ans)
            ans = f[i], beg = i - f[i] + 1, last = i;
    }
    //clog << endl;

    clog << ans << endl;
    fout << ans << endl;
    for (int i = pos[beg]; i <= pos[last]; i++)
    {
        clog << str[i];
        fout << str[i];
    }
    clog << endl;
    fout << endl;

    return 0;
}
