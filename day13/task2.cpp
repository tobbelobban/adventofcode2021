#include<iostream>
#include<vector>
#include <sstream>
#include <limits>
#include <unordered_map>
#include <algorithm>

using namespace std;

void print_state(const vector<vector<int>>& v, const int max_row, const int max_col) {
    for(int row = 0; row < max_row && row < v.size(); ++row) {
        for(int col = 0; col < max_col && col < v[0].size(); ++col) cout << (v[row][col] ? '#' : '.') << " ";
        cout << endl;
    }
}

int main(int argc, char const *argv[])
{
    string line;
    int col,row, pos, max_col = numeric_limits<int>::min(), max_row = max_col;
    vector<pair<int,int>> v;
    while(getline(cin,line) && line != "") {
        pos = line.find(',');
        col = stoi(line.substr(0,pos));
        row = stoi(line.substr(pos+1));
        if(col > max_col) max_col = col;
        if(row > max_row) max_row = row;
        v.push_back({row,col});
    }
    ++max_row, ++max_col;
    vector<vector<int>> multi_v(max_row, vector<int>(max_col,0));
    for(const pair<int,int>& p : v) multi_v[p.first][p.second] = 1;
    while(getline(cin,line)) {
        pos = line.find('=');
        const char axis = line[pos-1];
        const int fold_value = stoi(line.substr(pos+1));
        if(axis == 'x') {
            for(int row = 0; row < max_row; ++row) {
                for(int col = fold_value + 1; col < max_col; ++col) {
                    multi_v[row][fold_value + fold_value - col] = multi_v[row][col] || multi_v[row][fold_value + fold_value - col];
                }
            }
            max_col = fold_value;
        } else if(axis == 'y') {
            for(int row = fold_value + 1; row < max_row; ++row) {
                for(int col = 0; col < max_col; ++col) {
                    multi_v[fold_value + fold_value - row][col] = multi_v[row][col] || multi_v[fold_value + fold_value - row][col];
                }
            }
            max_row = fold_value;
        } else {
            cout << "ERROR: invalid axis = " << axis << endl; return 0;
        }
    }
    print_state(multi_v, max_row, max_col); cout << endl;
    return 0;
}
