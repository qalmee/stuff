#ifndef CHAINBUILDER_H
#define CHAINBUILDER_H

#include <functional>
#include <vector>
#include <set>

using namespace std;

class ChainBuilder
{
public:
    ChainBuilder();
    vector<string> *solve(unsigned int start_arg, pair<unsigned int, unsigned int> borders_arg,
                                        vector<pair<char, vector<string> > > *data_arg, bool isLP = true);
    unordered_map<string, string> *getParent();
private:
    pair<unsigned int, unsigned int> borders;
    vector <pair<char, vector<string>>> *data;
    unordered_map<char, vector <string>> map;
    unordered_map<string, string> *parent;
    vector <string> *ans;
    char target;
    void bfs(string current);
    void checkAnsForConditions(set<string> &s);


    bool isLP;
    const char empty = '&';

};

#endif
