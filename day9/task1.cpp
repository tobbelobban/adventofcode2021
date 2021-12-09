
#include<iostream>
#include<sstream>
#include<vector>

using namespace std;

int main(int argc, char const *argv[])
{
    string line;
    getline(cin,line);
    const int width = line.length();
    vector<vector<int>> v;
    do {
        vector<int> v_n(width,0);
        for(int i = 0; i < width; ++i) v_n[i] = (line[i] - '0');
        v.push_back(v_n);
    } while (getline(cin,line));     
    const int height = v.size(), min_row = 0, max_row = height - 1, min_col = 0, max_col = width - 1;
    // check four corners
    // top-left
    int ans = v[0][0] < v[0][1] && v[0][0] < v[1][0] ? v[0][0] + 1 : 0;
    // top-right
    ans += v[0][max_col] < v[0][max_col-1] && v[0][max_col] < v[1][max_col] ? v[0][max_col] + 1 : 0;
    // bottom-left
    ans += v[max_row][0] < v[max_row-1][0] && v[max_row][0] < v[max_row][1] ? v[max_row][0] + 1 : 0;
    // bottom-right
    ans += v[max_row][max_col] < v[max_row-1][max_col] && v[max_row][max_col] < v[max_row][max_col-1] ? v[max_row][max_col] + 1 : 0;
    // top & bottom rows
    for(int c = 1; c < max_col; ++c) {
        ans += v[0][c] < v[0][c-1] && v[0][c] < v[0][c+1] && v[0][c] < v[1][c] ? v[0][c] + 1 : 0;
        ans += v[max_row][c] < v[max_row][c-1] && v[max_row][c] < v[max_row][c+1] && v[max_row][c] < v[max_row-1][c] ? v[max_row][c] + 1 : 0;
    }
    // left & right columns
    for(int r = 1; r < max_row; ++r) {
        ans += v[r][0] < v[r-1][0] && v[r][0] < v[r][1] && v[r][0] < v[r+1][0] ? v[r][0] + 1 : 0;
        ans += v[r][max_col] < v[r-1][max_col] && v[r][max_col] < v[r][max_col-1] && v[r][max_col] < v[r+1][max_col] ? v[r][max_col] + 1 : 0;
    }
    // interior
    for(int r = 1; r < max_row; ++r) {
        for(int c = 1; c < max_col; ++c) {
            if(v[r][c] < v[r-1][c] && v[r][c] < v[r][c-1] && v[r][c] < v[r][c+1] && v[r][c] < v[r+1][c]) ans += v[r][c] + 1;
        }
    }
    cout << ans << endl;
    return 0;
}
