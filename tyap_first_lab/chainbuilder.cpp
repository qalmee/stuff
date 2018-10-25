#include "chainbuilder.h"

#include <queue>

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
    q.push(current);
    while (!q.empty())
    {
        auto s = q.front();
        q.pop();
        if (s.size() > borders.second) continue;
        bool terminal = true;
        for (unsigned int i = 0; i<s.size(); i++)
        {
            if (map.count(s[i]))
            {
                terminal = false;
                for (auto str : map[s[i]])
                {
                    q.push(s.replace(i, 1, str));
                }
                break;
            }
        }
        if (terminal && s.size() >= borders.first && s.size() <= borders.second)
        {
            ans->push_back(s);
        }

    }
    if (current.size() > borders.second){
        return;
    }

}
