/*
ID: jchenbr1
LANG: C++11
TASK: cowtour
 */
#include <iostream>
#include <fstream>
#include <vector>
#include <complex>
#include <iomanip>
using namespace std;

typedef complex<double> Point;

int main()
{
    ifstream fin("cowtour.in");
    ofstream fout("cowtour.out");

    int n;
    while (fin >> n)
    {
        vector<Point> pt(n);

        for (auto & p: pt)
        {   
            double x, y;
            fin >> x >> y;
            p = Point(x, y);
        }

        vector<vector<double> > path(n, vector<double>(n, 1e100));

        for (int i = 0; i < n; i++)
        {
            string row;
            fin >> row;

            for (int j = 0; j < n; j++)
                if (row[j] == '1')
                    path[i][j] = 
                        abs(pt[i] - pt[j]);
            path[i][i] = 0;
        }

        vector<vector<double> > opt(path);

        for (int w = 0; w < n; w++)
            for (int u = 0; u < n; u++)
                for (int v = 0; v < n; v++)
                    opt[u][v] = min(opt[u][v], opt[u][w] + opt[w][v]);

//        for (int i = 0 ; i < n ; i++, clog << endl)
//            for (int j = 0; j < n; j++)
//                clog << opt[i][j] << " ";

        vector<double> farest(n, 0);
        double radius = 0;
        for (int u = 0; u < n; u++)
            for (int v = 0; v < n; v++)
                if (opt[u][v] < 1e99)
                farest[u] = max(farest[u], opt[u][v]), radius = max(radius, opt[u][v]);

        double ans = 1e100;
        for (int u = 0; u < n; u++)
            for (int v = 0; v < n; v++)
                if (opt[u][v] > 1e99)
                    ans = min(ans, max(radius, abs(pt[u] - pt[v]) + farest[u] + farest[v]));

        clog << setprecision(6) << fixed << showpoint << ans << endl;
        fout << setprecision(6) << fixed << showpoint << ans << endl;
    }


    return 0;
}
