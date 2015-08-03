/*
ID: jchenbr1
LANG: C++11
TASK: spin
 */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <functional>
using namespace std;

int main()
{
    ifstream fin("spin.in");
    ofstream fout("spin.out");

    vector<int> speed(5, 0);
    vector<vector<pair<int, int> > > wedge(5);
    for (int idx = 0; idx < 5; idx++)
    {
        int m;
        fin >> speed[idx] >> m;
        wedge[idx].resize(m);
        for (auto & pr: wedge[idx])
            fin >> pr.first >> pr.second;
    }

    function<bool(int, int, int, int)> 
        checkWheels = [&](int idx, int time, int l, int len)
    {
        //if (time < 10) clog << "idx = " << idx << ", time = " << time << ", (" << l << ", " << l + len << ")" << endl;
        if (len < 0) return false;
        if (idx == 5) return true;

        int to_add = speed[idx] * time;
        for (auto & pr: wedge[idx])
        {
            int L = (pr.first + to_add) % 360, Len = pr.second;

            int x = max(l, L), y = min(l + len, L + Len);
            //if (time < 10) clog << "[" << x << ", " << y << "]" << endl;
            if (checkWheels(idx + 1, time, x, y - x))
                return true;

            if (l < L)
            {
                x = max(l + 360, L), y = min(l + 360 + len, L + Len);
                if (checkWheels(idx + 1, time, x % 360, y - x))
                    return true;
            }else
            {
                x = max(l, L + 360), y = min(l, L + 360 + len);
                if (checkWheels(idx + 1, time, x % 360, y - x))
                    return true;
            }
        }
        return false;
    };

    bool flag = true;
    for (int time = 0; time < 360; time ++)
        if (checkWheels(0, time, 0, 360))
        {
            flag = false;
            clog << time << endl;
            fout << time << endl;
            break;
        }
    if (flag)
    {
        clog << "none" << endl;
        fout << "none" << endl;
    }

    return 0;
}

