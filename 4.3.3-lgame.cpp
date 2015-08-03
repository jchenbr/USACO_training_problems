/*
ID: jchenbr1
LANG: C++11
TASK: lgame
 */
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
using namespace std;

int main()
{
    ifstream fin("lgame.in");
    ifstream din("lgame.dict");
    ofstream fout("lgame.out");
    
    int score[26] = 
    {
        2, 5, 4, 4, 1, 6, 5, 5,
        1, 7, 6, 3, 5, 2, 3, 5,
        7, 2, 1, 2, 4, 6, 6, 7, 5, 7
    };
    int lim [26] = {};

    string str;
    fin >> str;
    int len = str.size();
    for (auto ch: str) lim[ch - 'a'] += 1;

    map<string, vector<pair<int, string> > > dict;
    int ans = 0;
    vector<string> ans_list;

    clog << str << endl;
    while (din >> str && str != ".")
    {
        int tmp[26] = {}, tot = 0;
        bool flag = true;

        for (auto ch: str) 
        {
            tmp[ch - 'a'] += 1;
            if (tmp[ch - 'a'] > lim[ch - 'a']) flag = false;
            tot += score[ch - 'a'];
            //if (str == "jacuzzi") clog << " " << ch << " " << (int) ch - 'a' << " , " << score[ch - 'a'] << endl;
        }
        if (!flag) continue;
        ////clog << str << " " << flag << " " << tot << endl;

        if (tot > ans) ans_list.clear();
        if (tot >= ans)
        {
            ans = tot;
            ans_list.push_back(str);
        } 

        string another;
        another.resize(len - str.size());
        int idx = 0;
        for (int i = 0; i < 26; i++)
            for (int j = tmp[i]; j < lim[i]; j++)
                another[idx++] = 'a' + i;

        //clog << another << endl;
        if (dict.count(another))
        {
            for (auto & pr: dict[another])
            {
                if (tot + pr.first > ans) ans_list.clear();
                if (tot + pr.first >= ans)
                {
                    ans = tot + pr.first;
                    if (str < pr.second)
                        ans_list.push_back(str + " " + pr.second);
                    else 
                        ans_list.push_back(pr.second + " " + str);
                }
            }
        }

        if (len == 7 && str.size() == 3)
        {
            for (int i = 0; i < 4; i++)
            {
                if (i && another[i] == another[i - 1]) continue;

                string third = "";

                for (int j = 0; j < (int)another.size(); j++)
                    if (i != j)
                        third += another[j];

                for (auto & pr: dict[third])
                {
                    if (tot + pr.first > ans) ans_list.clear();
                    if (tot + pr.first >= ans)
                    {
                        ans = tot + pr.first;
                        if (str < pr.second)
                            ans_list.push_back(str + " " + pr.second);
                        else
                            ans_list.push_back(pr.second + " " + str);
                    } 
                }
            }
        }

        if (str.size() > 4) continue;
        string sstr = str;
        sort(sstr.begin(), sstr.end());
        if (dict.count(sstr) == 0) 
            dict[sstr] = vector<pair<int, string> >();
        dict[sstr].push_back(make_pair(tot, str));
    }
    
    sort(ans_list.begin(), ans_list.end());

    fout << ans << endl;
    clog << ans << endl;

    for (auto & s:ans_list)
    {
        fout << s << endl;
        clog << s << endl;
    }

    return 0;
}
