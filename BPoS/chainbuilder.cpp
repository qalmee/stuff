#include "chainbuilder.h"

#include <queue>
#include <QDebug>
#include <string>
#include <iostream>

ChainBuilder::ChainBuilder()
{

}

vector<string> *ChainBuilder::solve(unsigned int start_arg, pair<unsigned int, unsigned int> borders_arg,
                                    vector<pair<char, vector<string> > > *data_arg, bool isLP)
{
    this->isLP = isLP;
    parent = new unordered_map<string, string>();
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

unordered_map<string, string> *ChainBuilder::getParent()
{
    return parent;
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
        if (terminalCount == s.size() && s.size() >= borders.first && s.size() <= borders.second){
            set.insert(s);
            continue;
        }
        if (terminalCount > borders.second){
            continue;
        }
        bool terminal = true;
        for (int i = (isLP ? 0 : static_cast<int>(s.size()) - 1); (isLP ? (i < static_cast<int>(s.size())) : (i >= 0)); (isLP ? i++ : i--))
        {
            if (map.count(s[i]))
            {
                terminal = false;
                for (auto str : map[s[i]])
                {
                    auto s_tmp = s;
                    if (!str.size()){
                        s_tmp.erase(i, 1);
                        q.push(s_tmp);
                    }
                    else if (s_tmp.size() <= borders.second*1.9)
                    {
                        s_tmp.replace(i, 1, str);
                        q.push(s_tmp);
                    }
                    parent->emplace(s_tmp, s);
                }
                break;
            }
        }
    }

    checkAnsForConditions(set);

    ans->reserve(set.size());
    for (auto str : set){
        ans->push_back(str);
    }
//    for (auto x : *parent){
//        qDebug() << QString::fromStdString(x.first) << " " << QString::fromStdString(x.second);
    //    }
}

void ChainBuilder::checkAnsForConditions(set<string> &s)
{
    for (auto it = s.begin(); it != s.end(); it++){
        auto tmp = it;
    }
}
