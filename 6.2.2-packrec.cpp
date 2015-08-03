/*
ID: jchenbr1
LANG: C++11
TASK: packrec
 */
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;


int main()
{
    ifstream fin("packrec.in");
    ofstream fout("packrec.out");

    const int inf = 200 + 5;
    int n = 4;
    vector<int> x(n), y(n);
    for (int i = 0; i < n; i++)
    {
        fin >> x[i] >> y[i];
        if (x[i] > y[i]) swap(x[i], y[i]);
    }
    int idx[4] = {0, 1, 2, 3};

    int ans = inf * inf;
    vector<pair<int, int> > ans_list;

    function<void(int[4])> layout[5];

    auto check = [&](int X, int Y)
    {
        //clog << "X = " << X << ", Y = " << Y << endl;
        if (X > Y) swap(X, Y);

        if (X * Y < ans)
        {
            ans_list.clear();
            ans = X * Y;
        }

        if (X * Y == ans)
            ans_list.push_back(make_pair(X, Y));
        return ;
    };

    layout[0] = [&](int idx[4]) 
    {
        int X = 0, Y = 0;
        for (int i = 0; i < 4; i++)
            X += x[idx[i]], Y = max(Y, y[idx[i]]); 

        check(X, Y);
        return ;
    };

    layout[1] = [&](int idx[4])
    {
        int X = 0, Y = 0;
        for (int i = 1; i < 4; i++)
            X += x[idx[i]], Y = max(Y, y[idx[i]]);
        X = max(X, y[idx[0]]), Y += x[idx[0]];
        check(X, Y);
        return ;
    };

    layout[2] = [&](int idx[4])
    {
        int X = x[idx[1]] + x[idx[2]], Y = max(y[idx[1]], y[idx[2]]);
        X = max(X, y[idx[0]]), Y += x[idx[0]];
        X += x[idx[3]], Y = max(Y, y[idx[3]]);
        check(X, Y);
        return ;
    };

    layout[3] = [&](int idx[4])
    {
        int X = max(x[idx[0]], x[idx[1]]), Y = y[idx[0]] + y[idx[1]];
        for (int i = 2; i < 4; i++)
            X += x[idx[i]], Y = max(Y, y[idx[i]]);
        check(X, Y);
        return ;
    };

    layout[4] = [&](int idx[4])
    {
        if (
                y[idx[0]] < y[idx[1]] && 
                x[idx[0]] > x[idx[2]] &&
                x[idx[1]] < x[idx[3]]
                ) 
        {
            int X = max(x[idx[0]] + x[idx[1]], x[idx[2]] + x[idx[3]]);
            int Y = max(y[idx[0]] + y[idx[2]], y[idx[1]] + y[idx[3]]);
            check(X, Y);
        }else
        {
            int X = max(x[idx[0]], x[idx[2]]) + max(x[idx[1]], x[idx[3]]);
            int Y = max(y[idx[0]] + y[idx[2]], y[idx[1]] + y[idx[3]]);
            check(X, Y);
        }


        return ;
    };

    do{
        for (int msk = 0; msk < (1 << 4); msk++)
        {
            for (int i = 0; i < 4; i++)
                if (msk & (1 << i))
                    swap(x[i], y[i]);

            for (int j = 0; j < 5; j++)
                layout[j](idx);

            for (int i = 0; i < 4; i++)
                if (msk & (1 << i))
                    swap(x[i], y[i]);
        }
        //for (int i = 0; i < 4; i++) clog << idx[i] << " "; clog << endl;
    }while (next_permutation(idx, idx + 4));

    sort(ans_list.begin(), ans_list.end());
    fout << ans << endl;
    clog << ans << endl;

    for (int i = 0; i < (int)ans_list.size(); i++)
    {
        if (i && ans_list[i] == ans_list[i - 1]) continue;
        auto pr = ans_list[i];
        fout << pr.first << " " << pr.second << endl;
        clog << pr.first << " " << pr.second << endl;
    }

    return 0;
}
