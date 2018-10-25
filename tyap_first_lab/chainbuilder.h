#ifndef CHAINBUILDER_H
#define CHAINBUILDER_H

#include <functional>
#include <vector>

using namespace std;

class ChainBuilder
{
public:
    ChainBuilder();
    vector<string> *solve(unsigned int start_arg, pair<unsigned int, unsigned int> borders_arg,
                                        vector<pair<char, vector<string> > > *data_arg);
private:
    pair<unsigned int, unsigned int> borders;
    vector <pair<char, vector<string>>> *data;
    unordered_map<char, vector <string>> map;
    vector <string> *ans;
    char target;

    void bfs(string current);

    const char empty = '&';
};

#endif
