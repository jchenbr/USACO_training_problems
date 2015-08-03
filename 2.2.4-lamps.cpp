/*
ID: jchenbr
LANG: C++11
TASK: lamps
 */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;
int main()
{
    ifstream fin("lamps.in");
    ofstream fout("lamps.out");

    int n, c;
    while (fin >> n >> c)
    {
        vector<int> off, on;
        int tmp;
        while (fin >> tmp, tmp != -1) on.push_back(tmp);
        while (fin >> tmp, tmp != -1) off.push_back(tmp);

        auto getLampState = [&](int state, int idx)
        {
            return 
                (state >> 0 & 1) ^ 
                ((state >> 1 & 1) & (idx & 1)) ^
                ((state >> 2 & 1) & ((idx & 1) ^ 1))^
                ((state >> 3 & 1) & (idx % 3 == 1)) ^ 
                1;
        };
        clog << " - " << getLampState(0, 1) << endl;
        clog << " - " << getLampState(0, 2) << endl;
        clog << " - " << getLampState(0, 3) << endl;
        clog << " - " << getLampState(0, 4) << endl;
        clog << " - " << getLampState(0, 5) << endl;


        set<string> ans;
        for (int state = 0; state < (1 << 4); state ++ )
        {
            int sum = (state >> 0 & 1) + (state >> 1 & 1) + 
                (state >> 2 & 1) + (state >> 3 & 1);
            if (sum <= c && ((sum & 1) == (c & 1)))
            {
                bool flag = true;
                for (auto i: on)
                    if (getLampState(state, i) == 0)
                    {
                        flag = false;
                        break;
                    }

                for (auto i: off)
                    if (getLampState(state, i) == 1) 
                    {
                        flag = false;
                        break;
                    }
                if (!flag) continue;

                string str;
                str.resize(n);
                for (int i = 1; i <= n; i ++)
                    str[i - 1] = '0' + getLampState(state, i);
                clog << "state = " << state << ", " << str << endl;
                ans.insert(str); 
            }
        }
        if (ans.size() == 0)
            fout << "IMPOSSIBLE" << endl;

        for (auto & str: ans)
        {
            clog << str << endl;
            fout << str << endl;
        }

    }

    return 0;
}
