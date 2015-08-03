/*
ID: jchenbr1
LANG: C++11
TASK: dualpal
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
    ifstream fin("dualpal.in");
    ofstream fout("dualpal.out");

    int S, N;
    while (fin >> N >> S)
    {
        for (S = S + 1; N > 0 ; S += 1)
        {
            int count = 0;
            for (int B = 2; B <= 10 && count < 2; B++)
                count += isPal(S, B);
            if (count == 2)
            {
                fout << S << endl;
                clog << S << endl;
                N -= 1;
            }
        }
    }

    return 0;
}

