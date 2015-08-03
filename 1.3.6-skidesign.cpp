/*
ID: jchenbr1
LANG: C++11
TASK: skidesign
 */
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    ifstream fin("skidesign.in");
    ofstream fout("skidesign.out");

    int n;
    while (fin >> n)
    {
        vector<int> hills(n);
        for (auto & h: hills) fin >> h;

        sort(hills.begin(), hills.end());
        int ans = -1; 
        auto sqr = [](const int x){return x * x;};
        for (int l = 0; l + 17 <= 100; l++)
        {
            int r = l + 17, L = 0, R = 0;
            for (auto & h: hills)
                L += sqr(max(0, l - h)), R += sqr(max(0, h - r));
            if (ans == -1 || ans > L + R) ans = L + R;
        }
        fout << ans << endl;
        clog << ans << endl;
    }

    return 0;
}
