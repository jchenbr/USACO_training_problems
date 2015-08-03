/*
ID: jchenbr1
LANG: C++11
TASK: milk3
 */
#include <iostream>
#include <string>
#include <fstream>
#include <set>
#include <queue>
using namespace std;

int main()
{
    ifstream fin("milk3.in");
    ofstream fout("milk3.out");

    int lim[3];
    while (fin >> lim[0] >> lim[1] >> lim[2])
    {
        set<int> done;
        queue<int> que;

        que.push(lim[2]);

        while (!que.empty())
        {
            int state = que.front();
            que.pop();
            if (done.count(state)) continue;
            done.insert(state);

            int milk[3] = 
            {
                state / (lim[2] + 1) / (lim[1] + 1),
                state / (lim[2] + 1) % (lim[1] + 1),
                state % (lim[2] + 1)
            };
            clog << milk[0] << ", " << milk[1] << ", " << milk[2] << endl;

            for (int i = 0; i < 3; i++)
                for (int j = 0; j < 3; j++)
                    if (i != j)
                    {
                        int tmp = min(milk[i], lim[j] - milk[j]);
                        milk[i] -= tmp;
                        milk[j] += tmp;

                        que.push(
                                milk[0] * (lim[1] + 1) * (lim[2] + 1) + 
                                milk[1] * (lim[2] + 1) + 
                                milk[2]
                                );

                        milk[i] += tmp;
                        milk[j] -= tmp;
                    }
        }

        set<int> ans;
        for (auto & state : done) 
            if (state / (lim[2] + 1) / (lim[1] + 1) == 0)
                ans.insert(state % (lim[2] + 1));

        bool flag = false;
        for (auto & c : ans)
        {
            if (!flag)
                flag = true;
            else 
                fout << " ", clog << " ";
            fout << c;
            clog << c;
        }
        fout << endl;
        clog << endl;
    }

    return 0;
}
