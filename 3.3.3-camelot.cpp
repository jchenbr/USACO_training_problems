/*
ID: jchenbr1
LANG: C++11
TASK: camelot
 */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

int main()
{
    ifstream fin("camelot.in");
    ofstream fout("camelot.out");

    int R, C;
    while (fin >> R >> C)
    {
        int opt[R][C][R][C];  

        int k_opt[R][C][R][C];

        const int Inf = 1000000000; 
        int to_nxt[8][2] = 
        { 
            2, 1, -2, 1, 2, -1, -2, -1, 
            1, 2, -1, 2, 1, -2, -1, -2
        };

        int k_x, k_y,  y, ans = Inf;
        char ch;
        fin >> ch >> y;
        k_y = ch - 'A';
        k_x = y - 1;

        for (int i = 0; i < R; i++)
        {
            for (int j = 0; j < C; j++)
            {
                vector<pair<int, int> > que;
                que.reserve(R * C );

                for (int x = 0; x < R; x++)
                    for (int y = 0; y < C; y++)
                        k_opt[i][j][x][y] = opt[i][j][x][y] = Inf;

                que.push_back(make_pair(i, j));
                
                opt[i][j][i][j] = 0;
                int x, y, val;
                size_t idx = 0;
                while (idx < que.size())
                {
                    x = que[idx].first;
                    y = que[idx].second;
                    idx++;
                    val = opt[i][j][x][y];
                    k_opt[i][j][x][y] = opt[i][j][x][y] + max(abs(x - k_x) , abs(y - k_y));

                    for (int k = 0; k < 8; k++)
                    {
                        int u = x + to_nxt[k][0], v = y + to_nxt[k][1];
                        if (u < 0 || u >= R || v < 0 || v >= C) continue;
                        if (opt[i][j][u][v] > val + 1)
                            opt[i][j][u][v] = val + 1, que.push_back(make_pair(u, v));
                    }
                }
                {
                    queue<pair<int, int> > que;
                    for (x = 0; x < R; x++)
                        for (y = 0; y < C; y++)
                            if (k_opt[i][j][x][y] < Inf)
                                que.push(make_pair(x, y));
                    while (!que.empty())
                    {
                        x = que.front().first;
                        y = que.front().second;
                        val = k_opt[i][j][x][y];
                        que.pop();

                        for (int k = 0; k < 8; k++)
                        {
                            int u = x + to_nxt[k][0], v = y + to_nxt[k][1];
                            if (u < 0 || u >= R || v < 0 || v>= C) continue;
                            if (k_opt[i][j][u][v] > val + 1)
                                k_opt[i][j][u][v] = val + 1, que.push(make_pair(u, v)); 
                        }
                    }
                }
            }
        }
        clog << "?" << endl;


        vector<pair<int, int> > knight;

        while (fin >> ch >> y)
            knight.push_back(make_pair(y - 1, (int)ch - 'A')); 

        if (knight.empty())
        {
            fout << 0 << endl;
            clog << 0 << endl;
            continue;
        }

        for (int i = 0; i < R; i++)
            for (int j = 0; j < C; j++)
            {
                int sum = 0;

                for (int k = 0; k < (int)knight.size(); k++)
                {
                    sum += opt[knight[k].first][knight[k].second][i][j];
                    if (sum >= Inf) break;
                }
                if (sum >= Inf) continue;

                for (int k = 0; k < (int)knight.size(); k++)
                {
                    int tmp = sum 
                        - opt[knight[k].first][knight[k].second][i][j] 
                        + k_opt[knight[k].first][knight[k].second][i][j]; 

                    if (tmp < ans)
                        ans = tmp; 
                }
            }
        clog << ans << endl;
        fout << ans << endl;
    }


    return 0;
}
