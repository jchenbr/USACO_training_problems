/*
ID: jchenbr1
LANG: C++11
TASK: ttwo
 */
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <set>

using namespace std;

int main()
{
    ifstream fin("ttwo.in");
    ofstream fout("ttwo.out");

    int n = 10;
    vector<vector<bool> > obs(n + 2, vector<bool>(n + 2, true));

    string state;
    state.resize(6);

    clog << "?" << endl;
    for (int i = 1; i <= n; i++)
    {
        string row;
        fin >> row;
        for (int j = 1; j<= n; j++)
        {
            obs[i][j] = row[j - 1] == '*';
            if (row[j - 1] == 'F')
            {
                state[0] = i;
                state[1] = j;
                state[2] = 0;
            }

            if (row[j - 1] == 'C')
            {
                state[3] = i;
                state[4] = j;
                state[5] = 0;
            }
        }
    }

    clog << "?" << endl;
    set<string> apr;
    char nxt[4][2] = {-1, 0, 0, 1, 1, 0, 0, -1};

    int ans = 0;
    while (true)
    {
        //clog << "(" << ans << ") = ";
        //for (auto & s : state) clog << (int)(s) << ", "; clog << endl;
        
        if (apr.count(state) || 
                (state[0] == state[3] && state[1] == state[4]))
            break;

        apr.insert(state);

        if (obs[state[0] + nxt[state[2]][0]][state[1] + nxt[state[2]][1]])
            state[2] = (state[2] + 1) % 4;
        else
            state[0] += nxt[state[2]][0], state[1] += nxt[state[2]][1];

        if (obs[state[3] + nxt[state[5]][0]][state[4] + nxt[state[5]][1]])
            state[5] = (state[5] + 1) % 4;
        else
            state[3] += nxt[state[5]][0], state[4] += nxt[state[5]][1];
        ans += 1;
    }
    if (state[0] == state[3] && state[1] == state[4])
    {
        clog << ans << endl;
        fout << ans << endl;
    }else
    {
        clog << 0 << endl;
        fout << 0 << endl;
    }

    return 0;
}
