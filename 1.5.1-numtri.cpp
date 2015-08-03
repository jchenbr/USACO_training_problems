/*
ID: jchenbr1
LANG: C++11
TASK: numtri
 */
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

int main()
{
    ifstream fin("numtri.in");
    ofstream fout("numtri.out");

    size_t n;
    while (fin >> n)
    {
        vector<vector<int> > tri(n, vector<int>(n, 0));

        for (size_t row = 0; row < n; row++)
            for (size_t col = 0; col <= row; col++)
                fin >> tri[row][col];

        vector<vector<int> > opt(tri);
        for (size_t row = 0; row + 1 < n; row++)
            for (size_t col = 0; col <= row; col++)
            {
                opt[row + 1][col] = max(opt[row][col] + tri[row + 1][col], opt[row + 1][col]);
                opt[row + 1][col + 1] = max(opt[row][col] + tri[row + 1][col + 1], opt[row + 1][col + 1]);
            }

        int ans = 0;
        for (auto item : opt[n - 1])
            ans = max(ans, item);
        fout << ans << endl;
        clog << ans << endl;

    }

    return 0;
}
