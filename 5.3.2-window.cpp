/*
ID: jchenbr1
LANG: C++11
TASK: window
 */
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdio>
#include <map>
#include <algorithm>
#include <cctype>
#include <cassert>
#include <iomanip>
using namespace std;

struct Point
{
    int x, y;
};

struct Window
{
    int data[4];
    int & operator [](int idx)
    {
        assert(idx < 4);
        return data[idx];
    }
};

Window getOverlap(Window & lhs, Window & rhs)
{
    Window ret;

    ret[0] = max(lhs[0], rhs[0]);
    ret[1] = min(lhs[1], rhs[1]);
    ret[2] = max(lhs[2], rhs[2]);
    ret[3] = min(lhs[3], rhs[3]);
    
    return ret;
}

int getArea(Window & win)
{
    return max(0, win[1] - win[0]) * max(0, win[3] - win[2]);
}


int getID(char name)
{
    if (islower(name))
        return name - 'a';
    else if (isupper(name))
        return name - 'A' + 26;
    else if (isdigit(name))
        return name - '0' + 52;
    else
        return -1;
}

void printWin(Window & win)
{
    clog << win[0] << ", " << win[1] << ", " << win[2] << ", " << win[3] << " = " << getArea(win) << endl;
}

int main()
{
    ifstream fin("window.in");
    ofstream fout("window.out"); 

    char cmd;
    int bot = -1, top = 0;
    vector<int> id_pos(26 + 26 + 10);
    map<int, Window> pos_win;
    vector<bool> exist(26 + 26 + 10, false);
    vector<pair<Window, int> > tmp;
    tmp.reserve(100000);

    while (fin >> cmd)
    {
        //clog << "! cmd = " << cmd << endl;
        if (!islower(cmd)) continue;
        //clog << "cmd = " << cmd << endl;

        char name;
        int pos, id;
        Window win;

        if (cmd == 't')
        {
            fin >> name >> name;
            id = getID(name);
            pos = id_pos[id];

            pos_win[top] = pos_win[pos];
            id_pos[id] = top++;
            pos_win.erase(pos);
        }
        else if (cmd == 'b')
        {
            fin >> name >> name;
            id = getID(name);
            pos = id_pos[id];

            pos_win[bot] = pos_win[pos];
            id_pos[id] = bot--;
            pos_win.erase(pos);
        }
        else if (cmd == 'd')
        {
            fin >> name >> name;
            id = getID(name);
            pos = id_pos[id];

            pos_win.erase(pos);
        }
        else if (cmd == 'w')
        {

            fin >> name >> name;
            id = getID(name);
            pos = id_pos[id] = top++;

            char comma;
            fin >> comma >> win[0] >> comma >> win[2] >> comma >> win[1] >> comma >> win[3];
            if (win[0] > win[1]) swap(win[0], win[1]);
            if (win[2] > win[3]) swap(win[2], win[3]);
            pos_win[pos] = win;
        }
        else if (cmd == 's')
        {
            fin >> name >> name;
            id = getID(name);
            pos = id_pos[id];

            auto u = pos_win.find(pos);
            win = u->second;

            tmp.clear();
            tmp.push_back(make_pair(u->second, 0));
            for (auto v = next(u); v != pos_win.end(); v++)
            {
                for (int idx = (int)tmp.size() - 1; idx >=0; idx -= 1)
                {
                    win = getOverlap(v->second, tmp[idx].first);
                    int area = getArea(win);

                    if (area != 0)
                    {
                        if (getArea(tmp[idx].first) == area)
                            tmp.erase(tmp.begin() + idx);
                        else
                            tmp.push_back(make_pair(win, tmp[idx].second + 1));
                    }
                }
            }
            int ans = 0;
            for (auto & pr : tmp)
                if (pr.second & 1)
                    ans -= getArea(pr.first);
                else
                    ans += getArea(pr.first);



            fout << fixed << setprecision(3) << ans * 100.0 / (double) getArea(u->second) << endl;
            clog << fixed << setprecision(3) << ans * 100.0 / (double) getArea(u->second) << endl;
        }    
    }

    return 0;
}
