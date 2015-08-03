/*
ID: jchenbr1
LANG: C++11
TASK: runround
 */

#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>

using namespace std;

int main()
{
    ifstream fin("runround.in");
    ofstream fout("runround.out");

    int beg;
    while (fin >> beg)
    {
        auto isRunround = [](int num)
        {
            //clog << num << ": ";
            vector<int> digit;
            digit.reserve(32);
            for (;num;num/=10) 
                digit.push_back(num%10);

            vector<bool> ap(10, false);
            for (auto & d: digit) 
                if (d == 0 || ap[d]) 
                {
                    //clog << endl;
                    return false;
                }else
                    ap[d] = true;

            vector<int> vis(digit.size(), false);
            int idx, n = digit.size(), count = 0;
            
            for (idx = n - 1; !vis[idx] ; idx = ((idx - digit[idx]) % n + n ) % n)
            {
                vis[idx] = true;
                count += 1;
                //clog << "-" << idx;
            }
            //cout << endl;
            return idx == n - 1 && count == n;
        };

        for (int num = beg + 1; ; num+=1)
            if (isRunround(num))
            {
                fout << num << endl;
                clog << num << endl;
                break;
            }
    }

    return 0;
}
