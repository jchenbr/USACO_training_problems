/*
ID: jchenbr1
TASK: gift1
LANG: C++11
 */

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <fstream>
#include <algorithm>
#include <map>
#include <vector>

using namespace std;

class FriendsCircle
{
private:
    map<string, int > money_;

public:
    FriendsCircle(){}
    
    void addFriend(const string & str)
    {
        if (money_.count(str) > 0)
            return ;
        money_[str] = 0; 
    }

    int getMoneyByName(const string & name)
    {
        return money_[name];
    }

    void sendGift(
            string & sender,
            int budget,
            vector<string> & recevier)
    {
        if (recevier.size() == 0 ) return ;
        int piece = budget / recevier.size();
        int outcome = 0;
        for (auto & one : recevier)
        {
            if (money_.count(one) == 0) continue;
            outcome += piece;
            money_[one] += piece;
        }
        money_[sender] -= outcome;
    }

};

int main(int argc, char ** argv)
{
    ifstream fin("gift1.in");
    ofstream fout("gift1.out");
    
    FriendsCircle fc;
    int n_friend;
    fin >> n_friend;

    vector<string> name_list(n_friend);

    for(auto & one: name_list)
    {
        fin >> one;
        fc.addFriend(one);
    }

    string sender;
    while (fin >> sender)
    {
        int m, budget;
        fin >> budget >> m;
        vector<string> recevier(m);
        for (auto & one: recevier)
           fin >> one;
        fc.sendGift(sender, budget, recevier); 
    }

    for (auto & one: name_list)
    {
        fout << one << " " << fc.getMoneyByName(one) << endl;
        clog << one << " " << fc.getMoneyByName(one) << endl;
    }

    return 0;
}
