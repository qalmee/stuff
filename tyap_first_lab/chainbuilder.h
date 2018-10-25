#ifndef CHAINBUILDER_H
#define CHAINBUILDER_H

#include <functional>
#include <vector>

using namespace std;

class ChainBuilder
{
public:
    vector<string> *solve(unsigned int start, pair<unsigned int, unsigned int> borders,
                                        vector<pair<char, vector<string> > > *data);
private:
    static pair<unsigned int, unsigned int> borders;
    static vector <pair<char, vector<string>>> *data;
    static unordered_map<char, vector <string>> map;
    static vector <string> *ans;
    static char target;

    void bfs(string current);
};

#endif // CHAINBUILDER_H
