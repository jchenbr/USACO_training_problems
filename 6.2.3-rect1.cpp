/*
ID: jchenbr1
LANG: C++11
TASK: rect1
 */
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>
#include <functional>
using namespace std;

struct Rect
{
    int data[2][2];
    
    int * operator [](int idx)
    {return data[idx];}
};

inline bool isLegal (Rect & r)
{return r[0][0] < r[0][1] && r[1][0] < r[1][1];};

inline void getInterval (int a[2], int b[2], int c[2], int type)
{

    if (type == 0)
    {
        c[0] = a[0];
        c[1] = min(a[1], b[0]);
    }
    else if (type == 1)
    {    
        c[0] = max(a[0], b[0]);
        c[1] = min(a[1], b[1]);
    }else if (type == 2)
    {
        c[0] = max(a[0], b[1]);
        c[1] = a[1];
    }
};

inline bool cover(Rect & a, Rect & b)
{
    return a[0][0] <= b[0][0] && a[0][1] >= b[0][1] 
        && a[1][0] <= b[1][0] && a[1][1] >= b[1][1];
}

int main()
{
    ifstream fin("rect1.in");
    ofstream fout("rect1.out");

    vector<Rect> shape, Shape;
    vector<int>  color, Color;
    shape.reserve(100000);
    Shape.reserve(100000);
    color.reserve(100000);
    Color.reserve(100000);

    int R, C, m;



    auto splitRect = [&](Rect & a, Rect & b, int c)
    {
        Rect ret;
        for (int i = 0; i < 3; i ++)
            for (int j = 0; j < 3; j++)
            {
                if (i == 1 && j == 1) continue;
                getInterval(a[0], b[0], ret[0], i);
                getInterval(a[1], b[1], ret[1], j);
                if (isLegal(ret))
                    Shape.push_back(ret), Color.push_back(c);
            }
        return ;
    };

    auto addRect = [&](Rect & b, int c)
    {
        Shape.clear();
        Color.clear();

        for (int i = 0; i < (int)shape.size(); i++)
            splitRect(shape[i], b, color[i]);

        Shape.push_back(b);
        Color.push_back(c);

        shape = Shape;
        color = Color;
    };

    fin >> R >> C >> m;

    Rect rect;

    rect[0][0] = 0;
    rect[0][1] = R;
    rect[1][0] = 0;
    rect[1][1] = C;

    addRect(rect, 1);

#if 0
    for (int i = 0; i < (int) color.size(); i++)
    {
        clog << "[" << shape[i][0][0] << ", " << shape[i][0][1] << "], ";
        clog << "[" << shape[i][1][0] << ", " << shape[i][1][1] << "], ";
        clog << color[i] << endl;
    }
    clog << "--------------------------" << endl;
#endif
    vector<Rect> to_add(m);
    vector<int> to_c(m);
    vector<bool> vaild(m, true);

    for (int i = 0; i < m; i++)
    {
        fin >> to_add[i][0][0] >> to_add[i][1][0] 
            >> to_add[i][0][1] >> to_add[i][1][1];
        fin >> to_c[i];
    }

    for (int i = 0; i < m; i++)
        for (int j = i + 1; j < m; j++)
            if (cover(to_add[j], to_add[i])) 
            {
                vaild[i] = false;
                break;
            }

    for (int i = 0; i < m; i++)
    {
        if (!vaild[i]) continue;
        int col = to_c[i];
        Rect & rect  = to_add[i];
        addRect(rect, col);

#if 0
        for (int i = 0; i < (int) color.size(); i++)
        {
            clog << "[" << shape[i][0][0] << ", " << shape[i][0][1] << "], ";
            clog << "[" << shape[i][1][0] << ", " << shape[i][1][1] << "], ";
            clog << color[i] << endl;
        }
        clog << "--------------------------" << endl;
#endif
    }

    map<int, int> ans;
    for (int i = 0; i < (int)color.size(); i++)
        ans[color[i]] += (shape[i][0][1] - shape[i][0][0]) * (shape[i][1][1] - shape[i][1][0]);


    for (auto & pr : ans)
    {
        clog << pr.first << " " << pr.second << endl;
        fout << pr.first << " " << pr.second << endl;
    }
    clog << ans.size() << endl;

    return 0;
}
