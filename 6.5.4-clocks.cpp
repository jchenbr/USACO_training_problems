/*
ID: jchenbr1
LANG: C++11
TASK: clocks
 */
#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <queue>
using namespace std;

int main()
{
    ifstream fin("clocks.in");
    ofstream fout("clocks.out");


    vector<string> method {"ABDE", "ABC", "BCEF", "ADG", "BDEFH", "CFI", "DEGH", "GHI", "EFHI"};



    auto getVal = [&](int msk, int pos)
    {
        return msk >> (pos << 1) & 3;
    };

    auto setVal = [&](int msk, int pos, int val)
    {
        msk &= ~(3 << (pos << 1));
        msk |= val << (pos << 1);
        return msk;
    };

    auto printVal = [&](int msk)
    {
        for (int i = 0; i < 9; i++)
        {
            clog << (getVal(msk, i) + 1) * 3 << " ";
            if (i % 3 == 2) clog << endl;
        }
    };

    auto applyMethod = [&](int msk, int id)
    {
        int val, pos;
        for (auto & i : method[id])
        {
            pos = i - 'A';
            val = (getVal(msk, pos) + 1) & 3;
            msk = setVal(msk, pos, val);
        }
        return msk;
    };

    int s = 0;
    for (int i = 0; i < 9; i++)
    {
        int val;
        fin >> val;
        val = (val / 3) & 3;
        s = setVal(s, i, val);
    }

    unordered_map<int, pair<int, int> > apr {{s, make_pair(-1, -1)}};
    queue<int> que;
    que.push(s);

    while (!que.empty())
    {
        if (s == 0) break;
        int s = que.front();
        que.pop();
        //printVal(s);
        //clog << "----\n" ;
        //cin.get();

        for (int i = 0; i < 9; i++)
        {
            int nxt = applyMethod(s, i);
            if (apr.count(nxt)) continue;
            apr[nxt] = make_pair(i, s);
            que.push(nxt);
        }
    }
    clog << "?" << endl;

    vector<int> ans_list;
    for (int s = 0; apr[s].first >= 0; s = apr[s].second)
        ans_list.push_back(apr[s].first);

    for (auto it = ans_list.rbegin(); it != ans_list.rend(); it++)
    {
        if (it != ans_list.rbegin())
        {
            fout << " ";
            clog << " ";
        }
        fout << *it + 1;
        clog << *it + 1;
    }
    fout << endl;
    clog << endl;

    return 0;
}
