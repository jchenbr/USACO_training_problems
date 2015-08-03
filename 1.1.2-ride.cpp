/*
ID : jchenbr1
TASK : ride
LANG : C++11
*/

#include <iostream>
#include <fstream>
#include <functional>
using namespace std;

int main(int argc, char ** argv)
{
    ifstream fin("ride.in");
    ofstream fout("ride.out");

    string ufo, fan;
    fin >> ufo >> fan;

    function<int(string &, int )> count_ = 
        [&] (string & str , int idx = 0) -> int
        {
            if (idx == (int)str.size())
                return 1;
            auto ret = ((int)(str[idx] - 'A' + 1)*
                    count_(str, idx + 1)) % 47;
            clog << ret << endl;
            return ret;
        }; 

    auto count = bind(count_, placeholders::_1, 0);

    if (count(ufo) == count(fan))
        fout << "GO" << endl;
    else 
        fout << "STAY" << endl;

    return 0;
}
