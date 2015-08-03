/*
ID: jchenbr1
LANG: C++11
TASK: rectbarn
 */

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

vector<vector<bool> > avi(3000 + 1, vector<bool>(3000 + 1, true));

inline pair<int, int> mp(int a, int b)
{
    return make_pair(a, b);
}

int main()
{
    ifstream fin("rectbarn.in");
    ofstream fout("rectbarn.out");
    //freopen("rectbarn.in", "r", stdin);
    //freopen("rectbarn.out", "w", stdout);

    int n, m, p;
    fin >> n >> m >> p;
    {
        vector<int> up[2];
        vector<pair<int, int> > que;

        que.reserve(m + 2);

        int x, y, ans = 0;
        for (int i = 0; i < p; i++) 
        {
            fin >> x >> y;
            avi[x][y] = false;
        }

        up[0].resize(m + 2, 0);
        for (int i = 1; i <= n ; i++)
        {
            up[i & 1].resize(m + 2, 0);
            que.clear();
            que.push_back(mp(0, 0));
            pair<int, int> tail;
            for (int j = 1; j <= m + 1; j++)
            {
                up[i & 1][j] = (j <= m && avi[i][j]) ? up[~i & 1][j] + 1 : 0;

                while (que.size() && que.back().second >= up[i & 1][j])
                {
                    tail = que.back();
                    que.pop_back();

                    if (que.size())
                        ans = max(ans, (j - que.back().first - 1) * tail.second);
                }
                que.push_back(mp(j, up[i & 1][j]));
            }
        }

        fout << ans << endl;
        clog << ans << endl;
    }

    return 0;
}
