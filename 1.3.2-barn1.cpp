/*
ID: jchenbr1
LANG: C++11
TASK: barn1
 */

#include <iostream>
#include <fstream>
#include <bitset>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    ifstream fin("barn1.in");
    ofstream fout("barn1.out");

    int M, S, C;
    while (fin >> M >> S >> C)
    {
        vector<int> cow(C);
        for (auto & c : cow) fin >> c;

        sort(begin(cow), end(cow));
        vector<int> interval;
        interval.reserve(C);
        int to_blocked = 1;
        for (size_t idx = 1; idx < cow.size(); idx++)
        {
            to_blocked += cow[idx] > cow[idx - 1];
            if (cow[idx] <= cow[idx - 1] + 1) continue;
            interval.push_back(cow[idx] - cow[idx - 1] - 1);
            //clog << "interval : " << cow[idx - 1] << ", " << cow[idx];
            //clog << ", len = " << cow[idx] - cow[idx - 1] - 1 << endl;
        }
        int to_cover = interval.size() + 1;
        int to_choose = to_cover - M;

        clog << "to_cover : " << to_cover << endl;
        clog << "to_choose : " << to_choose << endl;

        sort(begin(interval), end(interval));
        int waste = 0;
        for (int idx = 0; idx < to_choose; idx ++)
        {
            waste += interval[idx];
            //clog << "choose : " << interval[idx] << endl;
        }

        fout << to_blocked + waste << endl;
        clog << to_blocked + waste << endl;
    }    


    return 0;
}
