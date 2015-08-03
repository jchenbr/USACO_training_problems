/*
ID: jchenbr1
LANG: C++11
TASK: palsquare
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

const string itos [21] = 
{
    "0", "1", "2", "3", "4", "5", "6", "7", "8", "9",
    "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K"
};

string getFormBase(int val, int B)
{
    string ret = "";
    while (val != 0)
    {
        ret = itos[val % B] + ret;
        val /= B;
    }
    return ret;
}

bool isPal(int val, int B)
{
   string str = getFormBase(val, B);
   for (size_t idx = 0; idx + idx < str.size(); idx ++)
       if (str[idx] != str[str.size() - idx - 1])
           return false;
   return true;
}

int main(int argc, char ** argv)
{
    ifstream fin("palsquare.in");
    ofstream fout("palsquare.out");

    int B, N = 300;
    while (fin >> B)
    {
        for (int i = 1; i<= N; i++)
            if ( isPal(i * i, B))
            {
                fout << getFormBase(i, B) << " " << getFormBase(i * i, B) << endl;
                clog << getFormBase(i, B) << " " << getFormBase(i * i, B) << endl;
            }
    }

    return 0;
}

