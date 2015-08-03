/*
ID: jchenbr1
LANG: C++11
TASK: cryptcow
 */
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <functional>
using namespace std;


int main()
{
    ifstream fin("cryptcow.in");
    ofstream fout("cryptcow.out");

    const string dest("Begin the Escape execution at the Break of Dawn");
    string line, str;
    while (getline(fin, line)) str += line;

    unordered_set<unsigned long long> apr;

    auto HashStr = [&](const string & str)
    {
#if 0
        return str;
#else
        unsigned long long h = 0, g ;
        for (size_t i = 0; i < str.size(); i++)
        {
            h = (h << 4) + str[i];
            g = h & 0xf0000000L;
            if (g)
                h ^= g >> 24;
            h &= ~g; 
        }
        return (h << 4LL) + (unsigned long long)str.size();
#endif
    };

    auto legal = [&](const string & str)
    {
        if ((str.size() - dest.size())%3 != 0) return false;
        size_t i, j;

        for (i = 0; i < str.size(); i++)
            if (str[i] == 'C')
                break;
            else if (str[i] != dest[i])
                return false;

        for (j = 0; j < str.size(); j++)
            if (str[str.size() - j] == 'W')
                break;
            else if (str[str.size() - j] != dest[dest.size() - j])
                return false;

        for (;i < str.size();i = j)
        {
            j = i + 1;
            if (str[i] != 'C' && str[i] != 'O' && str[i] != 'W')
            {
                for (; j < str.size(); j++)
                    if (str[j] == 'C' || str[j] == 'O' || str[j] == 'W')
                    {
                        if (dest.find(str.substr(i, j - i)) == string::npos)
                            return false;
                        else
                            break;
                    }
            }
        }

        return true;
    };

    string ret;
    auto transform = [&](const string & str, size_t iC, size_t iO, size_t iW)
    {
        ret.resize(str.size() - 3);
        size_t j = 0;
        for (size_t i = 0; i < iC; i++) ret[j++] = str[i];
        for (size_t i = iO + 1; i < iW; i++) ret[j++] = str[i];
        for (size_t i = iC + 1; i < iO; i++) ret[j++] = str[i];
        for (size_t i = iW + 1; i < str.size(); i++) ret[j++] = str[i];
        return ret;
    };

    function<bool(string)> dfs = [&](string str)
    {
        //clog << "str = " << str << endl;
        auto id = HashStr(str);
        if (apr.find(id) != apr.end()) return false;
        apr.insert(id);

        //clog << ".." << endl;
        if (str == dest) 
        {
            //clog << "! = "<< str << endl;
            return true;
        }
        
        //clog << "..." << legal(str) << endl;
        
        if (!legal(str)) return false;
        //clog << "...." << endl;

        for (size_t iO = 1; iO + 1 < str.size(); iO++)
            if (str[iO] == 'O')
                for (size_t iC = 0; iC < iO; iC++)
                    if (str[iC] == 'C')
                        for (size_t iW = str.size() - 1; iW > iO; iW--)
                            if (str[iW] == 'W')
                            {
                                if (dfs(transform(str, iC, iO, iW)))
                                {
                                    //clog << "? " << str << ", "<<ret<< endl;
                                    //clog << "- " << transform(str, iC, iO, iW) << endl;
                                    return true;
                                }
                            }
        return false;
    };

    if (str.size() >= dest.size() && dfs(str))
    {
        clog << apr.size() << endl;
        fout << "1 " << count(str.begin(), str.end(), 'C') << endl;
        clog << "1 " << count(str.begin(), str.end(), 'C') << endl;
    }
    else
    {
        clog << apr.size() << endl;
        fout << "0 0" << endl;
        clog << "0 0" << endl;
    }

    return 0;
}
