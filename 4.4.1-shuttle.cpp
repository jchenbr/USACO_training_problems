/*
ID: jchenbr
LANG: C++11
TASK: shuttle
 */
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <queue>
using namespace std;

typedef long long LL;

int main()
{
    ifstream fin("shuttle.in");
    ofstream fout("shuttle.out");

    int n;
    while (fin >> n)
    {
        LL beg = 0, fin = 0;
        for (int i = 0; i < n; i++) beg = beg << 2 | 1, fin = fin << 2 | 2;
        beg <<= 2;
        fin <<= 2;
        for (int i = 0; i < n; i++) beg = beg << 2 | 2, fin = fin << 2 | 1;

        auto  get_ID_vec = [&](const vector<int> & vec)
        {
           LL ret = 0;
            for (int i = 0; i <= n + n; i ++)
                ret |= ((LL)vec[i]) << (i << 1);
            return ret;
        };

        auto get_vec_ID = [&] (LL  ID)
        {
            vector<int> vec(n + n + 1);
            for (int i = 0; i <= n + n; i ++)
                vec[i] = ID >> (i << 1) & 3;
            return vec;
        };

#if 1
        {
            vector<int> now = get_vec_ID(beg);
            for (auto & s : now) clog << s << " "; clog << endl;
            now = get_vec_ID(fin);
            for (auto & s : now ) clog << s << " "; clog << endl;
        }
#endif

        unordered_map<LL, pair<int, LL> > apr;


        queue<LL> que;

        que.push(beg);
        apr[beg] = make_pair(n,-1);

        LL u, v;


        int count = 0;

#define bit(x, i) ((x) << ((i) << 1))
#define msk(x, i) (((x) >> ((i) << 1)) & 3)
        while (!que .empty())
        {
            u = que.front();

            que.pop();
            
            count ++ ;
#if 0
            if (count % 10000 == 0)
            {
                clog << "count = " << count <<endl;
                clog << "u = " << u << endl;
                for (auto & s : now) clog << s << " "; clog << endl;
            }
#endif 
            int i = apr[u].first;
                {
                    if (i - 2 >= 0 && msk(u, i - 2) == 2 && msk(u, i - 1) == 1)
                    {
                        v = (u & ~bit(3LL, i - 2) ) | bit(msk(u, i - 2), i);

                        if (apr.count(v) == 0) 
                        {
                            apr[v] = make_pair(i - 2, u);
                            que.push(v);
                        }
                    }

                    if (i - 1 >= 0 && msk(u, i - 1) == 2)
                    {
                        v = (u & ~bit(3LL, i - 1)) | bit(msk(u, i -1), i);

                        if (apr.count(v) == 0)
                        {
                            apr[v] = make_pair(i - 1, u);
                            que.push(v);
                        }
                    }

                    if (i + 1 <= n + n && msk(u, i + 1) == 1)
                    {
                        v = (u & ~bit(3LL, i + 1)) | bit(msk(u, i + 1), i);

                        if (apr.count(v) == 0)
                        {
                            apr[v] = make_pair(i + 1, u);
                            que.push(v);
                        }
                    }

                    if (i + 2 <= n + n && msk(u, i + 1) == 2 && msk(u, i + 2) == 1)
                    {
                        v = (u & ~bit(3LL, i + 2)) | bit(msk(u, i + 2), i);

                        if (apr.count(v) == 0)
                        {
                            apr[v] = make_pair(i + 2, u);
                            que.push(v);
                        }
                    }
                }
        }
        clog << "? = " << count << endl;

        vector<int> ans;
        for (LL cur = fin; apr[cur].second != -1; cur = apr[cur].second)
        {   
            //if (cur != 0)clog << "cur = " << cur << ", pre =" << apr[cur].second << ", i = " << apr[cur].first << endl;
            ans.push_back(apr[cur].first + 1);
        }

        clog << "??" << endl;

        count = 0;
        for (auto it = ans.rbegin(); it != ans.rend(); it++)
        {

            if (count % 20 == 0)
            {
                if (count)
                    fout << endl, clog << endl;
            }
            else
                fout << " ", clog << " ";

            count += 1;
            fout << * it;
            clog << * it;
        }
        fout << endl;
        clog << endl;
    }

    return 0;
}
