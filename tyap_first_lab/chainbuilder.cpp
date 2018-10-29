#include "chainbuilder.h"

#include <queue>
#include <set>

ChainBuilder::ChainBuilder()
{

}

vector<string> *ChainBuilder::solve(unsigned int start_arg, pair<unsigned int, unsigned int> borders_arg,
                                    vector<pair<char, vector<string> > > *data_arg)
{
    borders = borders_arg;
    data = data_arg;
    target = (*data_arg)[start_arg].first;
    ans = new vector <string> ();
    for (auto x : *data_arg){
        map[x.first] = x.second;
    }
    bfs(string(1, target));
    return ans;
}

void ChainBuilder::bfs(string current)
{
    queue<string> q;
    set<string> set;
    q.push(current);
    while (!q.empty())
    {
        auto s = q.front();
        q.pop();
        unsigned int terminalCount = 0;
        for (auto ch : s){
            if (!map.count(ch)) terminalCount++;
        }
        if (terminalCount > borders.second){
            continue;
        }
        bool terminal = true;
        for (unsigned int i = 0; i<s.size(); i++)
        {
            if (map.count(s[i]))
            {
                terminal = false;
                for (auto str : map[s[i]])
                {
                    auto s1 = s;
                    if (!str.size()){
                        s1.erase(i, 1);
                        q.push(s1);
                    }
                    else if (s1.size() <= borders.second*1.5) q.push(s1.replace(i, 1, str));
                }
                break;
            }
        }
        if (terminal && s.size() >= borders.first && s.size() <= borders.second)
        {
            set.insert(s);
        }

    }
    for (auto str : set){
        ans->push_back(str);
    }
}
