#include<iostream>
#include<vector>
#include<limits>
#include<queue>
#include<algorithm>

using namespace std;

#define REPEAT 4

typedef vector<vector<int>> field;

int cheapest_path(const field& f) {
    const int max_row = f.size(), max_col = f[0].size(), max = 300000;
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
    int cols_b4, rows_b4, cols_after, rows_after;
    while(getline(cin,line)) {
        vector<int> field_row;
        for(const char& c : line) field_row.push_back(c - '0');
        cols_b4 = field_row.size();
        const int len = field_row.size();
        for(int i = 0; i < REPEAT; ++i) {
            for(int j = 0; j < len; ++j) field_row.push_back(field_row[i*len + j] < 9 ? field_row[i*len + j] + 1 : 1);
        }
        f.push_back(field_row);
    }
    const int num_rows = f.size(), num_cols = f[0].size();
    rows_b4 = num_rows; cols_after = f[0].size();
    for(int i = 0; i < REPEAT; ++i) {
        for(int j = 0; j < num_rows; ++j) {
            vector<int> field_row(f[i*num_rows + j]);
            for(int k = 0; k < num_cols; ++k) {
                field_row[k] = field_row[k] < 9 ? field_row[k] + 1 : 1;
            }
            f.push_back(field_row);
        }
    }
    rows_after = f.size();
    cout << cheapest_path(f) << endl;
    cout << "Rows: " << rows_b4 << " -> " << rows_after << endl;
    cout << "Cols: " << cols_b4 << " -> " << cols_after << endl;
    return 0;
}
