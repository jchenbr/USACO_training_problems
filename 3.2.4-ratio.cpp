/*
ID: jchenbr1
LANG: C++11
TASK: ratios
 */
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main()
{
    ifstream fin("ratios.in");
    ofstream fout("ratios.out");

    vector<int> a(3), b(3), c(3), d(3);

    for (auto & item : d) fin >> item;
    for (auto & item : a) fin >> item;
    for (auto & item : b) fin >> item;
    for (auto & item : c) fin >> item;
    
    bool flag = true;
    for (int i = 0; flag && i <= 100; i++)
        for (int j = 0; flag && j <= 100; j++)
            for (int k = 0; flag && k <= 100; k++)
            {
                int t = 0;

                if (d[0] !=0 && (a[0] * i + b[0] * j + c[0] * k) % d[0] == 0) 
                    t = (a[0] * i + b[0] * j + c[0] * k) / d[0];
                else if (d[0] != 0) 
                    continue;
                else if (d[1] != 0 && (a[1] * i + b[1] * j + c[1] * k) % d[1] == 0)
                    t = (a[1] * i + b[1] * j + c[1] * k) / d[1];
                else if (d[1] != 0)
                    continue;
                else if (d[2] != 0 && (a[2] * i + b[2] * j + c[2] * k) % d[2] == 0)
                    t = (a[2] * i + b[2] * j + c[2] * k) / d[2];
                else if (d[2] != 0)
                    continue;

                if (
                        t > 0 &&  
                        a[0] * i + b[0] * j + c[0] * k == d[0] * t &&
                        a[1] * i + b[1] * j + c[1] * k == d[1] * t &&
                        a[2] * i + b[2] * j + c[2] * k == d[2] * t
                        )
                {
                    flag = false;
                    fout << i << " " << j << " " << k << " " << t << endl;
                    clog << i << " " << j << " " << k << " " << t << endl;
                }
            }
    if (flag)
    {
        fout << "NONE" << endl;
        clog << "NONE" << endl;
    }

    return 0;
}
