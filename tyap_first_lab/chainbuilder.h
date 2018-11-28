#ifndef CHAINBUILDER_H
#define CHAINBUILDER_H

#include <functional>
#include <vector>
#include <unordered_set>

using namespace std;

class ChainBuilder
{
public:
    ChainBuilder();
    vector<string> *solve(unsigned int start_arg, pair<unsigned int, unsigned int> borders_arg,
                                        vector<pair<char, vector<string> > > *data_arg);
    unordered_map<string, string> *getParent();
private:
    pair<unsigned int, unsigned int> borders;
    vector <pair<char, vector<string>>> *data;
    unordered_map<char, vector <string>> map;
    unordered_map<string, string> *parent;
    vector <string> *ans;
    char target;
    void bfs(string current);

    unordered_set<string> used;
    const char empty = '&';

};

#endif
