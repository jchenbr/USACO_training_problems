/*
ID: jchenbr1
LANG: C++11
TASK: contact
 */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
using namespace std;

int main()
{
    ifstream fin("contact.in");
    ofstream fout("contact.out");


    int L, R, N;
    while (fin >> L >> R >> N)
    {
        string str, to_add;
        while (fin >> to_add) str += to_add;

        map<pair<int, int> , int> count;
        
        for (int i = 0; i <(int)str.size(); i++)
        {
            int val = 0;
            for (int len = 0; len < R && len <= i; len ++)
            {
                val += (str[i - len] - '0') << len;
                if (len + 1 >= L)
                    count[make_pair(len + 1, val)] += 1;
            }
        }

        map<int, vector<pair<int, int> > > ans;
        for (auto & c : count)
        {
            if (ans.count(c.second) == 0)
                ans[c.second] = vector<pair<int,int> >(0);
            ans[c.second].push_back(c.first);
        }

        for (auto a = ans.rbegin(); a!= ans.rend(); a = next(a))
        {
            if (N == 0) break;
            N -= 1;
            clog << a->first << endl;
            fout << a->first << endl;

            bool flag = false;
            int count = 0;

            for (auto & pr: a->second)
            {

                string tmp;
                tmp.resize(pr.first);
                int val = pr.second;

                for (int i = 0; i < pr.first ; i++)
                    tmp[pr.first - i - 1] = '0' + (val & 1), val >>=1;

                if (flag)
                    if (count % 6)
                        fout << " " , clog << " ";
                    else
                        fout << endl, clog << endl;
                else
                    flag = true;

                count += 1;

                fout << tmp;
                clog << tmp;
            }
            fout << endl;
            clog << endl;
        }
    }

    return 0;
}
