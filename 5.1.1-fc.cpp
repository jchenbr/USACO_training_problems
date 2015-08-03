/*
ID: jchenbr1
LANG: C++11
TASK: fc
 */
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <stack>
#include <iomanip>
#include <cmath>
using namespace std;


struct Point
{
    double x, y;
    Point(){}
    Point(double X, double Y):x(X), y(Y){}
};
const double eps = 1e-9;

double mul(const Point & a, const Point & b)
{return a.x * b.y - a.y * b.x;}

Point red(const Point & a, const Point & b)
{return Point(a.x - b.x, a.y - b.y);}

Point c;

bool myComp_1(const Point & a, const Point & b)
{return mul(red(a, c), red(b, c)) > 0;}

bool myComp_2(const Point & a, const Point & b)
{return (abs(a.x - b.x) < eps) ? (a.y < b.y) : (a.x < b.x);}

double len(const Point & a)
{ return sqrt(a.x * a.x + a.y * a.y);}

int main()
{
    ifstream fin("fc.in");
    ofstream fout("fc.out");

    int n;
    while (fin >> n)
    {
        vector<Point> pt;
        pt.reserve(n + 1);
        pt.resize(n);
        for (auto & p: pt) 
            fin >> p.x >> p.y;
        sort(pt.begin(), pt.end(), myComp_2);
        c = pt[0];
        sort(pt.begin() + 1, pt.end(), myComp_1);
        pt.push_back(c);

        vector<Point> hull;
        hull.reserve(n + 1);
        int m = 0;

        for (auto & p : pt)
        {
            while (m > 1 && mul(red(hull[m - 1], hull[m - 2]), red(p, hull[m - 1])) < 0)
            {
                hull.pop_back();
                m -= 1;
            }
            hull.push_back(p);
            m += 1;
        }

        double ans = 0.0;
        for (int i = 1; i < m; i++)
        {   
            ans += len(red(hull[i], hull[i - 1]));
        }
        fout << fixed << setprecision(2) << ans << endl;
        clog << fixed << setprecision(2) << ans << endl;

    }

    return 0;
}
