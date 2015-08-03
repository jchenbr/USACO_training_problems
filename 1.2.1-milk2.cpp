/*
ID: jchenbr1
LANG: C++11
TASK: milk2
 */

#include <iostream>
#include <cstring>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char ** argv)
{

    ifstream fin("milk2.in");
    ofstream fout("milk2.out");

    int n;
    while (fin >> n)
    {
        vector<pair<int, int> > farmer(n);
        for (auto & john: farmer)
        {
            fin >> john.first >> john.second;
        }

        sort(begin(farmer), end(farmer));

        int ans_milk = farmer[0].second - farmer[0].first;
        int  ans_no_milk = 0;
        pair<int, int> last = farmer[0];

        for (auto & john: farmer)
        {
            ans_no_milk = max(ans_no_milk, john.first - last.second);

            if (john.first > last.second)
            {
                last = john;
            }else 
                last.second = max(last.second, john.second);

            ans_milk = max(ans_milk, last.second - last.first);

            clog << "[interval] " << last.first << ", " << last.second << endl;
        }

        fout << ans_milk << " " <<ans_no_milk << endl;
        clog << ans_milk << " " << ans_no_milk << endl;
    }

    return 0;
}
