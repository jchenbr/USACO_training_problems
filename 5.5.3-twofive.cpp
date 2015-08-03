/*
ID: jchenbr1
LANG: C++11
TASK: twofive
 */
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <functional>
#include <cstring>
using namespace std;

const int N = 6;
typedef long long LL;

struct State
{
    LL data[N][N][N][N][N];

    LL & operator [] (int idx[5])
    {
        return data[idx[0]][idx[1]][idx[2]][idx[3]][idx[4]];
    }

    State()
    {
        memset(data, -1, sizeof(data));
    }
};

void printIDX(int idx[], State & f)
{
    //clogg << idx[0] << ", " << idx[1] << ", " << idx[2] << ", " << idx[3] << ", " << idx[4];
    //clogg << " = " << f[idx] << endl;
}

LL getToTarget(string str)
{
    //clogg << "target = " << str << endl;

    vector<bool> used(26, false);
    vector<int> X(26), Y(26);

    for (int i = 0; i < (int)str.size(); i++)
    {
        int u = str[i] - 'A';
        used[u] = true;
        X[u] = i / 5;
        Y[u] = i % 5 + 1;
        //clogg << "used " << str[i] << " as " << u << ", " << X[u] << ", " << Y[u] << endl;
    }

    State f;
    
    function<LL(int, int[])> find = [&] (int cur, int idx[])
    {
        //clogg << "lv = " << cur << ", ";
        //    printIDX(idx, f);

        if (f[idx] >= 0) return f[idx];
        if (cur >= 25) return 1LL;

        if (used[cur])
        {
            int x = X[cur], y = Y[cur];

            if ( (x == 0 || idx[x] + 1 <= idx[x - 1]) && (idx[x] + 1 == y))
            {
                idx[x] += 1;
                LL val = find(cur + 1, idx);
                idx[x] -= 1;

                return f[idx] = val;
            }else
                return f[idx] = 0;
        }else
        {
            LL val = 0;
            for (int x = 0; x < 5; x++)
            {
                //clogg << "test " << x << endl;
                if (x == 0 || idx[x] + 1 <= idx[x - 1])
                {
                    if (idx[x] == 5) continue;
                    idx[x] += 1;
                    val += find(cur + 1, idx);
                    idx[x] -= 1;
                }
            }
            //printIDX(idx,f );
            return f[idx] = val;
        }

        return 0LL;
    };

    int idx [5] = {0, 0, 0, 0, 0};
    return find(0, idx);
}

int main()
{
    ifstream fin("twofive.in");
    ofstream fout("twofive.out");

    char cmd;
    fin >> cmd;
    if (cmd == 'W')
    {
        LL ans = 0;
        string str, tar;

        fin >> tar;
        //clogg << "tar = " << tar << endl;

        vector<bool> used(6, false); 
        for (int i = 0; i < 25; i++)
        {
            for (char j = 'A'; j < tar[i]; j++)
                if (!used[j - 'A'])
                {
                    ans += getToTarget(str + j);
                    //clogg << (str + j) << ", " << ans << endl;
                }
            str += tar[i];
            used[tar[i] - 'A'] = true;
        }
        ans += 1;
        //clogg << ans << endl;
        fout << ans << endl;
    }else
    {
        string str;
        LL n;
        fin >> n;
        vector<bool> vis(25);
        for (int i = 0; i < 25; i++)
        {
            char k = 0;
            for (char j = 'A'; j <= 'Y'; j++)
                if (!vis[j - 'A'])
                {
                    LL val = getToTarget(str + j);
                    //clogg << "val out = " << val << endl;
                    if (val < n)
                    {
                        n -= val;
                    }else
                    {
                        k = j;
                        break;
                    }
                }
            vis[k - 'A'] = true;
            //clogg << "i = " << i << ", k = " << k << ", n = " << n  << endl;
            str += k;
        }
        //clogg << str << endl;
        fout << str << endl;
    }

    return 0;
}
