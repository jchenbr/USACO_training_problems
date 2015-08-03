/*
ID: jchenbr1
LANG: C++11
TASK: prefix
 */

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

int main()
{
    ifstream fin("prefix.in");
    ofstream fout("prefix.out");

    vector<string> temp;
    string str, t;
    while (fin >> t, t!=".")
        temp.push_back(t);

    while (fin >> t) str += t;
    //clog << " str = " << str << endl;

    vector<bool> is_cap(str.size() + 1, false);
    is_cap[0] = true;

    for (int idx = 1; idx <= (int)str.size(); idx++)
    {
        for (auto & t: temp)
        {
            //clog << "- t = " << t << endl;
            if (idx >= (int)t.size() && is_cap[idx - t.size()])
            {
                bool flag = true;
                for (int j = 0; j < (int)t.size(); j++)
                {
                    //clog << "-- " << t[j] << " <>" << str[idx - t.size() + j] << endl;
                    if (t[j] != str[idx - t.size() + j])
                    {
                        flag = false;
                        break;
                    }
                }
                if (flag)
                {
                    is_cap[idx] = true;
                    break; 
                }
            }
        }
        //clog << "idx = " << idx << ", " << is_cap[idx] << endl;
    }

    for (int idx = (int)str.size(); idx >= 0; idx --)
        if (is_cap[idx])
        {
            fout << idx << endl;
            clog << idx << endl;
            break; 
        }
        
    return 0;
}
