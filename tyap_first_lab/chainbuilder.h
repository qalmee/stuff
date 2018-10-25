#ifndef CHAINBUILDER_H
#define CHAINBUILDER_H

#include <QObject>
#include <functional>
#include <vector>

using namespace std;

class ChainBuilder
{
    Q_OBJECT
public:
    ChainBuilder(unsigned int start, pair<unsigned int, unsigned int> borders, vector <pair<char, vector<string>>> *data);
    vector <string>* solve();
    virtual ~ChainBuilder();
private:
    pair<unsigned int, unsigned int> borders;
    vector <pair<char, vector<string>>> data;
    unordered_map<char, vector <string>> map;
    vector <string> ans;
    char target;

    void bfs(string current);
};

#endif // CHAINBUILDER_H
