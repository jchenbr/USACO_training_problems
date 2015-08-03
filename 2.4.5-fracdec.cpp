/*
ID: jchenbr1
LANG: C++11
TASK: fracdec
 */
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <queue>
using namespace std;

int main()
{
    ifstream fin("fracdec.in");
    ofstream fout("fracdec.out");

    int A, B;
    while (fin >> A >> B)
    {
        int L = B + 1;
        ostringstream sout;
        queue<int> que;
        map<int, int> apr;
        que.push(A/B);
        A %= B;

        for(int i = 0; A; i++)
        {
            if (apr.count(A))
            {
                L = apr[A];
                break;
            }
            apr[A] = i;

            A *= 10;
            que.push(A/B);
            A %= B;
        }

        //clog << que.front();
        sout << que.front();
        que.pop();

        if (!que.empty()) 
        {
            //clog << ".";
            sout << ".";
        }else
            sout << ".0"; //clog << ".0";

        for (int i = 0; !que.empty(); i++)
        {
            if (i == L) 
            {
                //clog << "(";
                sout << "(";
            }
            //clog << que.front();
            sout << que.front();
            que.pop();
        }

        if (A)
        {
            //clog << ")";
            sout << ")";
        }

        //clog << endl;
        
        string str = sout.str();
        for (int i = 0; i < (int)str.size(); i++)
        {
            if (i && i % 76 == 0) fout << endl;
            fout << str[i];
        }
        fout << endl;

    }

    return 0;
}
