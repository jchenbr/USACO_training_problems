/*
ID: jchenbr1
LANG: C++11
TASK: castle
 */

#include <iostream>
#include <cstdio>
#include <string>
#include <fstream>
#include <vector>
#include <functional>

using namespace std;

int main()
{
    ifstream fin("castle.in");
    ofstream fout("castle.out");

    int n, m;
    while (fin >> m >> n)
    {
        vector<vector<bool> > castle((n + 1) << 1, vector<bool>((m + 1) << 1, false));

        int to_wall[4][2] = {0, -1, -1, 0, 0, 1, 1, 0};
        int to_room[4][2] = {0, -2, -2, 0, 0, 2, 2, 0};

        for (int x = 1; x <= n; x++)
            for (int y = 1; y <= m; y++)
            {
                int state;
                fin >> state;
                for (int d = 0; d < 4; d++)
                    castle[(x << 1) + to_wall[d][0]][(y << 1) + to_wall[d][1]] = state >> d & 1;
            }
        for (int x = 0; x < (n + 1) * 2; x++, clog << endl)
            for (int y = 0; y < (m + 1) * 2; y++)
                if ( x > 1 && y > 1 && (x & 1) == 0 && (y & 1) ==0 ) 
                    clog << " ";
                else
                {
                    if (castle[x][y])
                        clog << "#" ;
                    else
                        clog << "O" ; 
                }

        function<int(vector<vector<bool> > &, int , int)> travel = 
            [&](vector<vector<bool> > & castle, int x, int y) -> int
        {
            if (x < 2 || x > (n << 1) || y < 2 || y > (m << 1)) return 0;
            if (castle[x][y]) return 0;
            castle[x][y] = true;

            int ret = 1;
            for (int d = 0; d < 4; d++)
                if (!castle[x + to_wall[d][0]][y + to_wall[d][1]])
                    ret += travel(castle, x + to_room[d][0], y + to_room[d][1]); 

            return ret;
        };

        int room_count = 0, room_max = -1;
        vector<vector<bool> > tmp(castle);

        for (int x = 1; x <= n; x++)
            for (int y = 1; y <= m; y++)
            {
                int area = travel(tmp, x << 1, y << 1);
                if (area)
                {
                    room_count += 1;
                    room_max = max(area, room_max);
                }
            }

        fout << room_count << endl << room_max << endl;
        clog << room_count << endl << room_max << endl;

        char to_direct[4] = {'W', 'N', 'E', 'S'};
        int wall_x, wall_y, wall_d, merge_max = -1;
        for (int y = 1; y <= m; y++)
            for (int x = n; x >= 1; x--)
                for (int d = 1; d <= 2; d++)
                    if (castle[(x << 1) + to_wall[d][0]][(y << 1) + to_wall[d][1]])
                    {
                        tmp = vector<vector<bool> >(castle);
                        tmp[(x << 1) + to_wall[d][0]][(y << 1) + to_wall[d][1]] = false;
                        //clog << x << ", " << y << ", " << d << endl;
                        int area = travel(tmp, x << 1, y << 1);
                        if (area > merge_max)
                        {
                            merge_max = area;
                            wall_x = x;
                            wall_y = y;
                            wall_d = d;
                        }

                    }

        fout << merge_max << endl << wall_x << " " << wall_y << " " << to_direct[wall_d] << endl;
        clog << merge_max << endl << wall_x << " " << wall_y << " " << to_direct[wall_d] << endl;
    }

    return 0;
}
