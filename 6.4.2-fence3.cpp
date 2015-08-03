/*
ID: jchenbr1
LANG: C++11
TASK: fence3
 */
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <iomanip>
#include <set>
using namespace std;

inline double getLength(const double dx, const double dy)
{
    return sqrt(dx * dx + dy * dy);
}

int main()
{
    ifstream fin("fence3.in");
    ofstream fout("fence3.out");

    int n ;
    fin >> n;
    vector<vector<double> > fence(n);
    set<double> xs, ys;
    double y_l = 100.0, y_r = 0.0, x_l = 100.0, x_r = 0.0;
   
    for (auto & f: fence) 
    {
        f.resize(4);

        for (auto & item : f) fin >> item;

        if (f[0] > f[2]) swap(f[0], f[2]);

        if (f[1] > f[3]) swap(f[1], f[3]);

        xs.insert(f[0]);
        xs.insert(f[2]);

        ys.insert(f[1]);
        ys.insert(f[3]);

        y_l = min(f[1], y_l);
        y_r = max(f[3], y_r);

        x_l = min(f[0], x_l);
        x_r = max(f[2], x_r);
    }

    /*
    bool is_swapped = false;
    clog << (xs.size() * (y_r - y_l) / 0.1) << ", " << (ys.size() * (x_r - x_l) / 0.1) << endl;
    if (xs.size() * (y_r - y_l) > ys.size() * (x_r - x_l))
    {
        is_swapped = true;
        
        swap(xs, ys);
        
        swap(y_l, x_l);
        swap(y_r, x_r);

        for (auto f: fence)
            swap(f[0], f[1]), swap(f[2], f[3]);
    }
    clog << (xs.size() * (y_r - y_l) / 0.1) << ", " << (ys.size() * (x_r - x_l) / 0.1) << endl;
    */

    double ans = 1e100, ans_x, ans_y;

    auto getCost = [&](const double x, const double y)
    {
        double ret = 0.0;
        for (auto & f : fence)
        {
            if (f[0] < x && x < f[2] )
                ret += min(abs(y - f[1]), abs(y - f[3]));
            else if (f[1] < y && y < f[3])
                ret += min(abs(x - f[0]), abs(x - f[2]));
            else
                ret += min(getLength(x - f[0], y - f[1]), getLength(x - f[2], y - f[3]));
        }
        return ret;
    };

    auto cmpCost = [&](const double x_1, const double x_2, const double y)
    {
        double ret_1 = 0.0, ret_2 = 0.0;
        for (auto & f: fence)
        {
            if (f[1] < y && y < f[3])
            {
                ret_1 += min(abs(x_1 - f[0]), abs(x_1 - f[2]));

                ret_2 += min(abs(x_2 - f[0]), abs(x_2 - f[2]));
            }
            else
            {
                if (f[0] < x_1 && x_1 < f[2])
                    ret_1 += min(abs(y - f[1]), abs(y - f[3]));
                else
                    ret_1 += min(
                            getLength(x_1 - f[0], y - f[1]), 
                            getLength(x_1 - f[2], y - f[3])
                            );

                if (f[0] < x_2 && x_2 < f[2])
                    ret_2 += min(abs(y - f[1]), abs(y - f[3]));
                else
                    ret_2 += min(
                            getLength(x_2 - f[0], y - f[1]),
                            getLength(x_2 - f[2], y - f[3])
                            );
            }
        }

        return ret_1 < ret_2;
    };
    

    //clog << "y will be within {" << y_l << ", " << y_r << "}"<< endl;
    //for (auto x : xs) clog << x << " " ; clog << endl;
    static const double _one_third = 1.0 / 3.0;
    static const double _two_third = 2.0 / 3.0;

    auto searchAns = [&](const double y)
    {
        double ret_x, ret = 1e100;

        double last_x = * xs.begin();
        for (auto px = next(xs.begin()); px != xs.end(); ++px)
        {
            double l = last_x, r = *px, x_1, x_2;
            //clog << " go " << l << ", " << r << endl;

            while (r - l > 1e-2)
            {
                x_1 = l * _two_third + r * _one_third;
                x_2 = l * _one_third + r * _two_third;
#if 1
                if (cmpCost(x_1, x_2, y))
                    r = x_2;
                else
                    l = x_1;
#else
                if (getCost(x_1, y) < getCost(x_2, y))
                    r = x_2;
                else
                    l = x_1;
#endif
            }
            double tmp = getCost(l, y);
            if (tmp < ret)
            {
                ret = tmp;
                ret_x = l;
            }
            last_x = *px;
        }
        return make_pair(ret, ret_x);
    };

    //double last_y = * ys.begin();
    //for (auto py = next(ys.begin()); py != ys.end(); ++py)
    {
        double y_1, y_2, l = y_l, r = y_r;
        //clog << "----------------------------\n";
        while (r - l > 1e-2)
        {
            y_1 = _two_third * l + _one_third * r;
            y_2 = _one_third * l + _two_third * r;
            //clog << y_1 << ", " << y_2 << ", " << l << ", " << r << endl; 
            //auto res_1 = searchAns(y_1), res_2 = searchAns(y_2);
            //clog << "[" << res_1.first << ", " << res_1.second << "], [" << res_2.first << ", " << res_2.second << "]" << endl;

            if (searchAns(y_1) < searchAns(y_2))
                r = y_2;
            else
                l = y_1;
        }
        auto pr = searchAns(l);
        if (pr.first < ans)
        {
            ans = pr.first;
            ans_x = pr.second;
            ans_y = l;
        }
        //last_y = *py;
    }


    //if (is_swapped) swap(ans_x, ans_y);

    fout << fixed << setprecision(1) << ans_x << " " << ans_y << " " << ans << endl;
    clog << fixed << setprecision(1) << ans_x << " " << ans_y << " " << ans << endl;

    return 0;
}
