/*
ID: jchenbr1
LANG: C++11
TASK: cowcycle
*/
#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>
#include <functional>
#include <cmath>
using namespace std;

inline double sqr(double x){return x * x;}

int main()
{
    ifstream fin("cowcycle.in");
    ofstream fout("cowcycle.out");

    int F, R, F1, F2, R1, R2;
    fin >> F >> R >> F1 >> F2 >> R1 >> R2;

    vector<int> ans_F(F), tmp_F(F);
    vector<int> ans_R(R), tmp_R(R);
    vector<double> tmp(F * R);
    double ans = 1e100;
    
    int F_l, F_r, R_l, R_r;

    auto calc = [&]()
    {
        //clog << "!" << endl;
        //for (auto & f : tmp_F) clog << f << " "; clog << endl;
        //for (auto & f : tmp_R) clog << f << " "; clog << endl;
        tmp.clear();
        for (auto & f : tmp_F)
            for (auto & r: tmp_R)
                tmp.push_back(f * 1.0 /r);


        for (size_t i = 0; i < tmp.size(); i++)
            for (size_t j = i + 1; j < tmp.size(); j++)
                if (tmp[i] > tmp[j]) swap(tmp[i], tmp[j]);
        double variance = 0;
        double average = 0;

        for (size_t i = 1; i < tmp.size(); i++)
            average += tmp[i] - tmp[i - 1];

        average /= tmp.size() -1;

        for (size_t i = 1; i < tmp.size(); i++)
            variance += sqr(tmp[i] - tmp[i - 1] - average);

        variance /= tmp.size() - 1;

        if (variance < ans)
        {
            ans = variance;
            ans_F = tmp_F;
            ans_R = tmp_R;
        }
    };

    function<void(int, int, int, int)> dfs = [&](int F_i, int F_beg, int R_i, int R_beg)
    {
        //if (F_i + R_i <= 4){
        //    clog << "(" << F_i << ", " << F_beg << ", " << R_i << ", " << R_beg << ")" << endl;
        //}
        if (F_i + 1 >= F && R_i + 1 >= R)
        {
            calc();
        }
        else if (F_i + 1 >= F)
        {
            for (tmp_R[R_i] = R_beg; tmp_R[R_i] <= R_r - (R - R_i - 1); tmp_R[R_i] ++)
                dfs(F_i, F_beg, R_i + 1, tmp_R[R_i] + 1); 
        }
        else 
        {
            for (tmp_F[F_i] = F_beg; tmp_F[F_i] <= F_r - (F - F_i - 1); tmp_F[F_i] ++)
                dfs(F_i + 1, tmp_F[F_i] + 1, R_i, R_beg);
        }
    };

    //clog << F1 << ", " << F2 << ", " << R1 << ", " << R2 << endl;
    for (F_l = F1; F_l <= F2; F_l++)
        for (F_r = F1 + F - 1; F_r <= F2; F_r++)
        {
            for (R_l = R1; R_l <= R2; R_l++)
            {
                for (R_r = R1 + R - 1 ; R_r <= R2; R_r++)
                {
                    if (3 * F_l * R_l > F_r * R_r) continue;
                    //clog << "[" << F_l << ", " << F_r << ", " << R_l << ", " << R_r << "]"<< endl;
                    tmp_F[0] = F_l, tmp_F[F - 1] = F_r;
                    tmp_R[0] = R_l, tmp_R[R - 1] = R_r;
                    dfs(1, F_l + 1, 1, R_l + 1);
                }
            }
        }
    //clog << "ans = " << ans << endl;

    for (int i = 0; i < F; i++)
    {
        if (i)
        {
            fout << " ";
            clog << " ";
        }
        fout << ans_F[i];
        clog << ans_F[i];
    }
    fout << endl;
    clog << endl;

    for (int i = 0; i < R; i++)
    {
        if (i)
        {
            fout << " ";
            clog << " ";
        }
        fout << ans_R[i];
        clog << ans_R[i];
    }
    fout << endl;
    clog << endl;

    return 0;
}
