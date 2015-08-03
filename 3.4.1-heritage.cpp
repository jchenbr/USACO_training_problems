/*
ID: jchenbr
LANG: C++11
TASK: heritage
 */
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <functional>
using namespace std;

int main()
{
    ifstream fin("heritage.in");
    ofstream fout("heritage.out");

    string pre, in;
    while (fin >> in >> pre)
    {
        function<string(size_t, size_t, size_t, size_t)> dfs
            = [&](size_t l, size_t r, size_t x, size_t y) -> string
            {
                //clog << "in = (" << l << ", " << r << "), pre = [" << x << ", " << y << "]"<< endl;
                if (l == r) return "";

                for (size_t i = x; i < y; i++)
                    if (in[i] == pre[l])
                    {
                        size_t len = i - x;
                        //clog << "\tin = " << l << ", pre = " << i << ", len = " << len << endl;
                        //clog << "\t\t<" << l + 1 << ", " << l + 1 + len << ">, <" 
                            //<< x << ", " << x + len << ">" << endl;  
                        //clog << "\t\t<" << l + 1 + len << ", " << r << ">, <" 
                            //<< x + len + 1 << ", " << y << ">" << endl;  
                        return 
                            dfs(l + 1, l + 1 + len, x, x + len) +
                            dfs(l + 1 + len, r, x + len + 1, y) + 
                            pre[l];
                    }
                return "";
            };
        fout << dfs(0, pre.size(), 0, in.size()) << endl;
        //clog << dfs(0, pre.size(), 0, in.size()) << endl;
    }

    return 0;
}
