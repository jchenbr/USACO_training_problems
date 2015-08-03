/*
ID: jchenbr1
TASK: beads
LANG: C++
 */

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main(int argc, char ** argv)
{
    ifstream fin("beads.in");
    ofstream fout("beads.out");

    int n;
    string necklace;
    fin >> n >> necklace;
    vector<int> color((n << 1) + 2, 0);
    vector<vector<int> > 
        prefix(2, vector<int>((n << 1) + 2, 0));
    vector<vector<int> > 
        subfix(2, vector<int>((n << 1) + 2, 0));

    for (int idx = 0; idx < n; idx++)
    {
        color[idx + 1] = color[idx + 1 + n] = 
            (necklace[idx]=='r') << 1 | (necklace[idx]=='b');
    }

    for (int j = 0; j < 2; j++)
        for (int idx = 1; idx <= n + n; idx ++)
            prefix[j][idx] = (color[idx] == 1 << (j ^ 1)) ? 0 : prefix[j][idx - 1] + 1;

    for (int j = 0; j < 2; j++)
        for (int idx = n + n; idx > 0; idx--)
            subfix[j][idx] = (color[idx] == 1 << (j ^ 1)) ? 0 : subfix[j][idx + 1] + 1;

    int ans = 0;

    for (int idx = 1; idx < n + n; idx ++)
        ans = max(ans, min(n, 
                    max(prefix[0][idx], prefix[1][idx]) +  
                    max(subfix[0][idx + 1], subfix[1][idx + 1])
                    )
                ); 
    fout << ans << endl;
    clog << ans << endl;
    
    return 0;
}
