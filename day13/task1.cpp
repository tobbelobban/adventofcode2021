#include<iostream>
#include<vector>
#include <sstream>
#include <limits>
#include <unordered_map>
#include <algorithm>

using namespace std;

int main(int argc, char const *argv[])
{
    string line;
    int x,y, pos, max_x = numeric_limits<int>::min(), max_y = max_x;
    vector<pair<int,int>> v;
    while(getline(cin,line) && line != "") {
        pos = line.find(',');
        x = stoi(line.substr(0,pos));
        y = stoi(line.substr(pos+1));
        if(x > max_x) max_x = x;
        if(y > max_y) max_y = y;
        v.push_back({x,y});
    }
    ++max_x, ++max_y;
    getline(cin,line);
    pos = line.find('=');
    const char axis = line[pos-1];
    const int fold_value = stoi(line.substr(pos+1));
    vector<vector<int>> multi_v(max_y, vector<int>(fold_value,0));
    for(const pair<int,int>& p : v) {
        if(p.first < fold_value) {
            multi_v[p.second][p.first] = 1;
        } else if(p.first > fold_value) {
            multi_v[p.second][fold_value - (p.first - fold_value)] = 1;
        }
    }
    int ans = 0;
    for(int row = 0; row < multi_v.size(); ++row) {
        for(int col = 0; col < fold_value; ++col) ans += multi_v[row][col];
    }
    cout << ans << endl;
    return 0;
}
