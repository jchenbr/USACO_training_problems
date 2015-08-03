/*
ID: jchenbr1
LANG: C++11
TASK: namenum
 */ 
#include <iostream>
#include <fstream>
#include <string>
#include <memory.h>
#include <set>
#include <vector>

using namespace std;

class Dict
{
private:
    struct Node
    {
        int count;
        Node* nxt[26];
        Node (){count = 0;memset(nxt, 0, sizeof(nxt));};
    };
    Node* root;
    void insert(const char str[])
    {
        for (Node * cur = root; str; str++)
        {           
            size_t idx = *str - 'A';
            clog << *str << ", " << idx << endl;
            if (cur->nxt[idx] == NULL)
                cur->nxt[idx] = new Node;
            cur = cur->nxt[idx];
            cur->count += 1;
        }
        clog << endl; 
    }
    int count(const char str[]) const
    {
        Node * cur ;
        for (cur = root; str; str++)
        {
            size_t idx = * str - 'A';
            if (cur->nxt[idx] == NULL) return 0;
            cur = cur->nxt[idx];
        }
        return cur->count;
    }
public:
    Dict(){root = new Node;}

    void insert(const string & str)
    {
        Node * cur = root;
        for (size_t i = 0; i < str.size(); i++)
        {
            size_t idx = str[i] - 'A';
            if (cur->nxt[idx] == NULL)
                cur->nxt[idx] = new Node;
            cur = cur -> nxt[idx];
        }
        cur -> count += 1;
    }

    int count(const string & str) const 
    {
        Node * cur = root;
        for (size_t i = 0; i< str.size(); i++)
        {
            size_t idx = str[i] - 'A';
            if (cur->nxt[idx] == NULL)
                return 0;
            cur = cur->nxt[idx];
        }
        return cur->count;
    }
};
 
const string itos [10] =
{
    "", "", "ABC", "DEF", "GHI", "JKL", "MNO", "PRS", "TUV", "WXY"
};

bool dfs(const string & num, size_t idx, string cur, const Dict & dict, ofstream & fout)
{
    if (idx < num.size())
    {
        bool ret = false;
        for (auto ch: itos[num[idx] - '0'])
            ret = dfs(num, idx + 1, cur + ch , dict, fout) || ret;
        return ret;
    }else
    {
        if (dict.count(cur) == 0)
            return false;
        fout << cur << endl;
        clog << cur << endl;
        return true;
    }
}

int main(int argc, char ** argv)
{
    Dict dict;
    ifstream dict_in("dict.txt");
    string str;
    while (dict_in >> str)
        dict.insert(str);
    clog << " Dictionary is good." << endl;

    ifstream fin("namenum.in");
    ofstream fout("namenum.out");

    string num;
    while (fin >> num)
    {
        if (!dfs(num, 0, "", dict, fout))
        {
            fout << "NONE" << endl;
            clog << "NONE" << endl;
        }
    }
}
