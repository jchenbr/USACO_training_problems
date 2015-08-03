/*
ID: jchenbr1
LANG: C++11
TASK: transform
 */

#include <iostream>
#include <fstream>
#include <cstdio>
#include <vector>
#include <string>

using namespace std;

vector<string> rotate( const vector<string> & pat)
{
    int n = pat.size();
    vector<string> ret = pat;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            ret[j][n - i - 1] = pat[i][j];
    
    return ret;
}

vector<string> flip( const vector<string> & pat)
{
    int n = pat.size();
    vector<string> ret = pat;
    for (int i = 0; i < n; i++)    
        for (int j = 0; j < n; j++)
            ret[i][n - j - 1] = pat[i][j];
    return ret;
}

bool is_equal( const vector<string> & a, const vector<string> & b)
{
    int n = a.size();
    for (int i = 0; i < n; i++) 
        if (a[i] != b[i]) return false;
    return true;
}

int main(int argc, char ** argv)
{
    ifstream fin("transform.in");
    ofstream fout("transform.out");

    int n;
    while (fin >> n)
    {
        vector<string> a(n) ,b(n);
        for (auto & row: a)
        {
             fin >> row;
             clog << row << "," << row.size() <<endl;
        }
        for (auto & row: b)
            fin >> row;


        clog << "- " << endl;
        vector<string> tmp = rotate(a);
        clog << "- " << endl;
        for (auto & row: tmp)
            clog << row << endl;
        clog << "- " << endl;
        tmp = flip(a);
        for (auto & row: b)
            clog << row << endl;
        clog << "- " << endl;

        if ( is_equal(rotate(a), b) )
            fout << "1" << endl, clog << "1" << endl;
        else if ( is_equal( rotate(rotate(a)), b) )
            fout << "2" << endl, clog << "2" << endl;
        else if ( is_equal( rotate(rotate(rotate(a))), b) )
            fout << "3" << endl, clog << "3" << endl;
        else if ( is_equal(flip(a), b) )
            fout << "4" << endl, clog << "4" << endl;
        else if ( is_equal(flip(a), rotate(b)) ||
                  is_equal(flip(a), rotate(rotate(b))) ||
                  is_equal(flip(a), rotate(rotate(rotate(b)))) )
            fout << "5" << endl, clog << "5" << endl;
        else if ( is_equal(a, b) )
            fout << "6" << endl, clog << "6" << endl;
        else 
            fout << "7" << endl, clog << "7" << endl;

    }

    return 0;
}
