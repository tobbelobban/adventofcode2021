#include<iostream>
#include<vector>
#include<limits>
#include<queue>
#include<algorithm>

using namespace std;

typedef vector<vector<int>> field;

int cheapest_path(const field& f) {
    const int max_row = f.size(), max_col = f[0].size(), max = 1000;
    vector<vector<int>> costs(max_row, vector<int>(max_col, max));
    costs[0][0] = 0;
    bool changed;
    int top, right, bottom, left;
    do {
        changed = false;
        for(int row = 0; row < max_row; ++row) {
            for(int col = 0; col < max_col; ++col) {
                top = max, right = max, bottom = max, left = max;
                if(row > 0) {
                    top = costs[row-1][col];
                } 
                if(row < max_row - 1) {
                    bottom = costs[row+1][col];
                }
                if(col > 0) {
                    left = costs[row][col-1];
                }
                if(col < max_col - 1) {
                    right = costs[row][col+1];
                }
                int min_neighbour = min({top,right,bottom,left});
                if(min_neighbour + f[row][col] < costs[row][col]) {
                    costs[row][col] = min_neighbour + f[row][col];
                    changed = true;
                }
            }
        }
    } while(changed);

    return costs[max_row-1][max_col-1];
}

int main(int argc, char const *argv[])
{
    string line;
    field f;
    while(getline(cin,line)) {
        vector<int> field_row;
        for(const char& c : line) field_row.push_back(c - '0');
        f.push_back(field_row);
    }
    cout << cheapest_path(f) << endl;
    return 0;
}
