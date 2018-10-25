#include "chainbuilder.h"

#include <queue>

vector<string> *ChainBuilder::solve(unsigned int start, pair<unsigned int, unsigned int> borders,
                                    vector<pair<char, vector<string> > > *data)
{
    this->borders = borders;
    this->data = data;
    this->target = (*data)[start].first;
    for (auto x : *data){
        map[x.first] = x.second;
    }
    bfs(string(1, target));
    return &ans;
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
            ans.push_back(s);
        }

    }
    if (current.size() > borders.second){
        return;
    }

}
