/*
ID: jchenbr1
LANG: C++11
TASK: snail
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <functional>
#include <cstring>
using namespace std;

int ans;
int nxt[125][125][4];
int drc[4][2] = {0, -1, -1, 0, 0, 1, 1, 0};
bool vis[125][125];

void dfs(int x, int y, int D, int tot)
{
    //clog << x << ", " << y << " -> " << D << ", tot = " << tot << endl;
    ans = max(ans, tot);
    for (int d = (D + 1) % 4, count = 0; count < 2 ; d = (d + 2) % 4, count += 1)
    {
        if (nxt[x][y][d] == 0) continue;
        bool flag = true;

        int u = x, v = y;
        for (int step = 1; step <= nxt[x][y][d]; step++)
        {
            if (vis[u + drc[d][0]][v + drc[d][1]])
            {
                //clog << "[" << u << ", " << v << "] = " << tot + step - 1 << endl;

                ans = max(ans, tot + step - 1);
                flag = false;
                break;
            }
            u += drc[d][0], v += drc[d][1];
        }

        if (flag)
        {
            u = x, v = y;
            for (int step = 1; step <= nxt[x][y][d]; step++)
            {
                u += drc[d][0], v += drc[d][1];
                vis[u][v] = true;
            }

            dfs(u, v, d, tot + nxt[x][y][d]);

            u = x, v = y;
            for (int step = 1; step <= nxt[x][y][d]; step++)
            {
                u += drc[d][0], v += drc[d][1];
                vis[u][v] = false;
            }
        }
    }
    return ;
}

int main()
{
    ifstream fin("snail.in");
    ofstream fout("snail.out");
    
    int n, m;
    while (fin >> n)
    {
        m = n;
        bool a[n + 2][m + 2];
        memset(a, 0, sizeof(a));
        memset(nxt, 0, sizeof(nxt));

        int B;
        fin >> B;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                a[i][j] = true;

        clog << "----" << endl;
        while (B--)
        {
            int x;
            char y;
            fin >> y >> x;
            a[x][y - 'A' + 1] = false;
            clog << x << ", " << y - 'A' + 1 << endl;
        }
        clog << "?" << endl;


        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
            {
                for (int d = 0; d < 2; d++)
                    if (a[i + drc[d][0]][j + drc[d][1]])
                        nxt[i][j][d] = nxt[i + drc[d][0]][j + drc[d][1]][d] + 1;
                    else
                        nxt[i][j][d] = 0;
            }

        for (int i = n; i >= 1; i--)
            for (int j = m; j >= 1; j--)
            {
                for (int d = 2; d < 4; d++)
                    if (a[i + drc[d][0]][j + drc[d][1]])
                        nxt[i][j][d] = nxt[i + drc[d][0]][j + drc[d][1]][d] + 1;
                    else
                        nxt[i][j][d] = 0;
            }

        memset(vis, 0, sizeof(vis));
        ans = 0;

        
        clog << "|" << endl;
        vis[1][1] = true;
        dfs(1, 1, 0, 1);
        dfs(1, 1, 1, 1);
        fout << ans << endl;
        clog << ans << endl;
    }

    return 0;
}
