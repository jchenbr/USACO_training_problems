/*
ID: jchenbr1
LANG: C++11
TASK: maze1
 */
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

int main()
{
    ifstream fin("maze1.in");
    ofstream fout("maze1.out");

    int w,h;
    while (fin >> w >> h)
    {
        vector<vector<bool> > avi(h + h + 3, vector<bool>(w + w + 3, false));

        string row;
        getline(fin, row);

        for (int i = 0; i < h + h + 1; i ++)
        {
            getline(fin, row);
            for (int j = 0; j < w + w + 1; j++)
                avi[i + 1][j + 1] = row[j] == ' ';
        }
        for (int i = 1; i <= h + h + 1; i++, clog << endl)
            for (int j = 1; j <= w + w + 1; j++)
                clog << avi[i][j] ;
        clog << "?" << endl;

        
        int x, y, u, v;

        int to_wall[4][2] = {-1, 0, 0, 1, 1, 0, 0, -1};
        int to_room[4][2] = {-2, 0, 0, 2, 2, 0, 0, -2};

        vector<vector<int> > vis(h + h + 2, vector<int>(w + w + 2, 0));
        queue<pair<int,int> > que;

        for (int i = 1; i <= h; i++)
            for (int j = 1; j <= w; j++)
            {
                for (int d = 0; d < 4; d++)
                {
                    u = i + i + to_wall[d][0];
                    v = j + j + to_wall[d][1];
                    if ((u < 2 || u > h + h || v < 2 || v > w + w ) &&
                        (avi[u][v]))
                    {
                        que.push(make_pair(i << 1, j << 1));
                        vis[i << 1][j << 1] = 1;
                        avi[u][v] = false;
                    }
                }

                if (i == h && j == w)
                {
                    for (int d = 0; d < 4; d++)
                        clog << avi[i + i + to_wall[d][0]][j + j + to_wall[d][1]] << " ";
                    clog << endl;
                }
            }

        
        int ans = 0;
        while (!que.empty())
        {
            x = que.front().first;
            y = que.front().second;
            ans = max(ans, vis[x][y]);
            que.pop();

            for (int d = 0; d < 4; d++)
            {
                if (avi[x + to_wall[d][0]][y + to_wall[d][1]] && 
                        0 == vis[x + to_room[d][0]][y + to_room[d][1]])
                {
                    que.push(make_pair(x + to_room[d][0], y + to_room[d][1]));
                    vis[x + to_room[d][0]][y + to_room[d][1]] = vis[x][y] + 1;
                }
            }
        }
        clog << ans << endl;
        fout << ans << endl;

    }

    return 0;
}
