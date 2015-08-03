/*
ID: jchenbr1
LANG: C++11
TASK: combo
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <set>

using namespace std;

int main(int argc, char ** argv)
{
    ifstream fin("combo.in");
    ofstream fout("combo.out");

    int n;
    while (fin >> n)
    {
        vector<int> pw_j(3), pw_m(3);
        for (auto & d: pw_j) fin >> d, d -= 1;
        for (auto & d: pw_m) fin >> d, d -= 1;

        set<int> allowed;

        for (int i = -2; i < 3; i++)
            for (int j = -2; j < 3; j++)
                for (int k = -2; k < 3; k ++)
                {
                    allowed.insert(
                            (pw_j[0] + i + n) % n * n * n + 
                            (pw_j[1] + j + n) % n * n +
                            (pw_j[2] + k + n) % n);
                    allowed.insert(
                            (pw_m[0] + i + n) % n * n * n +
                            (pw_m[1] + j + n) % n * n +
                            (pw_m[2] + k + n) % n);
                }

        fout << allowed.size() << endl;
        clog << allowed.size() << endl;
    }

    return 0;
}
