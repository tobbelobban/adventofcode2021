#include<algorithm>
#include<iostream>
#include<sstream>
#include<vector>
#include<queue>

using namespace std;

typedef vector<vector<int>> myvec;

int basin_size(int i, int j, const int lim_i, const int lim_j, const myvec& v, myvec& marked) {
    if(marked[i][j]) return 0;
    int size = 0;
    queue<pair<int,int>> q;
    q.push({i,j});
    marked[i][j] = 1;
    while(!q.empty()) {
        int remaining = q.size();
        while(remaining--) {
            const pair<int,int>& p = q.front(); q.pop();
            i = p.first; j = p.second;
            if(i > 0) {
                if(v[i][j] < v[i-1][j] && !marked[i-1][j] && v[i-1][j] != 9) {
                    q.push({i-1,j});
                    marked[i-1][j] = 1;
                }   
            }
            if(i < lim_i-1) {
                if(v[i][j] < v[i+1][j] && !marked[i+1][j] && v[i+1][j] != 9) {
                    q.push({i+1,j});
                    marked[i+1][j] = 1;
                }   
            }
            if(j > 0) {
                if(v[i][j] < v[i][j-1] && !marked[i][j-1] && v[i][j-1] != 9) {
                    q.push({i,j-1});
                    marked[i][j-1] = 1;
                }   
            }
            if(j < lim_j-1) {
                if(v[i][j] < v[i][j+1] && !marked[i][j+1] && v[i][j+1] != 9) {
                    q.push({i,j+1});
                    marked[i][j+1] = 1;
                }   
            }
            ++size;
        }
    }
    return size;
}

int main(int argc, char const *argv[])
{
    string line;    
    getline(cin,line);
    const int width = line.length();
    myvec marked;
    myvec v;
    vector<int> sizes;
    do {
        vector<int> v_n(width,0), marked_line(width,0);
        for(int i = 0; i < width; ++i) v_n[i] = line[i] - '0';
        v.push_back(v_n);
        marked.push_back(marked_line);
    } while(getline(cin,line));
    const int height = v.size(), min_row = 0, max_row = height - 1, min_col = 0, max_col = width - 1;
    // check four corners
    // top-left
    if(v[0][0] < v[0][1] && v[0][0] < v[1][0]) sizes.push_back(basin_size(0,0,height,width,v,marked));
    // top-right
    if(v[0][max_col] < v[0][max_col-1] && v[0][max_col] < v[1][max_col]) sizes.push_back(basin_size(0,max_col,height,width,v,marked));
    // bottom-left
    if(v[max_row][0] < v[max_row-1][0] && v[max_row][0] < v[max_row][1])  sizes.push_back(basin_size(max_row,0,height,width,v,marked));
    // bottom-right
    if(v[max_row][max_col] < v[max_row-1][max_col] && v[max_row][max_col] < v[max_row][max_col-1]) sizes.push_back(basin_size(max_row,max_col,height,width,v,marked));
    // top & bottom rows
    for(int c = 1; c < max_col; ++c) {
        if(v[0][c] < v[0][c-1] && v[0][c] < v[0][c+1] && v[0][c] < v[1][c]) sizes.push_back(basin_size(0,c,height,width,v,marked));
        if(v[max_row][c] < v[max_row][c-1] && v[max_row][c] < v[max_row][c+1] && v[max_row][c] < v[max_row-1][c]) sizes.push_back(basin_size(max_row,c,height,width,v,marked));
    }
    // left & right columns
    for(int r = 1; r < max_row; ++r) {
        if(v[r][0] < v[r-1][0] && v[r][0] < v[r][1] && v[r][0] < v[r+1][0]) sizes.push_back(basin_size(r,0,height,width,v,marked));
        if(v[r][max_col] < v[r-1][max_col] && v[r][max_col] < v[r][max_col-1] && v[r][max_col] < v[r+1][max_col]) sizes.push_back(basin_size(r,max_col,height,width,v,marked));
    }
    // interior
    for(int r = 1; r < max_row; ++r) {
        for(int c = 1; c < max_col; ++c) {
            if(v[r][c] < v[r-1][c] && v[r][c] < v[r][c-1] && v[r][c] < v[r][c+1] && v[r][c] < v[r+1][c]) sizes.push_back(basin_size(r,c,height,width,v,marked));
        }
    }
    sort(sizes.begin(),sizes.end());
    const int len = sizes.size();
    cout << sizes[len-1] * sizes[len-2] * sizes[len-3] << endl;
    return 0;
}
