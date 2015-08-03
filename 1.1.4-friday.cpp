/*
ID: jchenbr1
TASK: friday
LANG: C++11
 */

#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char ** argv)
{
    auto countWeekdaysOf13th = [] (int y)
    {
        int days_of_month [2][13] = 
        {
            0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31,
            0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
        }; 

        auto isLeapYear = [] (int y)
        {
            return y % 400 == 0 || (y % 100 != 0 && y % 4 ==0);
        };

        int y_ = 1900, m_ = 1, d_ = 0, wd_ = 1;
        vector<int> count(7, 0);
        while (y_ - 1900 < y)
        {
            d_ += 1;
            wd_ = (wd_ + 1) % 7;

            if (d_ > days_of_month[isLeapYear(y_)][m_])
            {
                d_ = 1;
                m_ += 1;
            }

            if (m_ > 12)
            {
                m_ = 1;
                y_ += 1;
            } 

            if (d_ == 13)
                count[ wd_ ] += 1;
        }

        return count;
    };

    ifstream fin("friday.in");
    ofstream fout("friday.out");

    int y;
    while (fin >> y)
    {
        bool is_lead = true;
        for (auto & one: countWeekdaysOf13th(y))
        {
            if (is_lead)
                is_lead = false;
            else
            {
                fout << " ";
                clog << " ";
            }
            fout << one;
            clog << one;
        }
        fout << endl;
        clog << endl;
    }

    return 0;
}
