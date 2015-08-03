/*
ID: jchenbr1
LANG: C++11
TASK: preface
 */
#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>

using namespace std;

int main()
{
    ifstream fin("preface.in");
    ofstream fout("preface.out");

    int n;
    while (fin >> n)
    {
        int num_to_local[10][3] = 
        {
            0, 0, 0, 
            1, 0, 0, 2, 0, 0, 3, 0, 0, 
            1, 1, 0, 0, 1, 0, 1, 1, 0, 
            2, 1, 0, 3, 1, 0, 1, 0, 1
        };
        
        int local_to_global[3][3] = 
        {
            0, 1, 2, 2, 3, 4, 4, 5, 6
        };
        
        char global_to_char[8] = "IVXLCDM";

        int global_count[7] = {0, 0, 0, 0, 0, 0, 0};
        
        for (int i = 1; i <= n; i++)
        {
            int num = i;
            for (int j = 0; num && j < 3; j++)
            {
                int local_count[3];
                memcpy(local_count, num_to_local[num % 10], sizeof(int) * 3);
                global_count[local_to_global[j][0]] += local_count[0];
                global_count[local_to_global[j][1]] += local_count[1];
                global_count[local_to_global[j][2]] += local_count[2];
                num /= 10;
            }
            global_count[6] += num;
        }

        for (int i = 0; i < 7; i++)
            if (global_count[i])
            {
                clog << global_to_char[i] << " " << global_count[i] << endl;
                fout << global_to_char[i] << " " << global_count[i] << endl;
            }
    }

    return 0;
}
