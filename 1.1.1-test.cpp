/*
 ID : jchenbr1
 TASK : test
 LANG : C++11
 */

#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char ** argv)
{
    ifstream fin("test.in");
    ofstream fout("test.out");

    int a, b;
    fin >> a >> b;
    fout << a + b << endl;

    return 0;
}
