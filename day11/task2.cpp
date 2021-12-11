#include<iostream>
#include<vector>
#include<queue>

#define HEIGHT 10
#define WIDTH 10

using namespace std;

void print_state(const vector<vector<int>>& v) {
    for(int r = 0; r < HEIGHT; ++r) {
        for(int c = 0; c < WIDTH; ++c) cout << v[r][c] << " ";
        cout << endl;
    }
}

unsigned long flashes(vector<vector<int>>& v) {
    unsigned long num_flashes = 0;
    queue<pair<int,int>> incremented;
    for(int row = 0; row < HEIGHT; ++row) {
        for(int col = 0; col < WIDTH; ++col) {
            if(v[row][col] > 9) {
                v[row][col] = 0; ++num_flashes;
                incremented.push({row,col});
            }
            int remain;
            while(!incremented.empty()) {
                remain = incremented.size();
                while(remain--) {
                    const pair<int,int> p = incremented.front(); incremented.pop();
                    const int& r = p.first, & c = p.second;
                    for(int i = r - 1; i < r + 2; ++i) {
                        for(int j = c - 1; j < c + 2; ++j) {
                            if(i < 0 || i >= HEIGHT || j < 0 || j >= WIDTH || !v[i][j]) continue;
                            if(++v[i][j] > 9) {
                                v[i][j] = 0; ++num_flashes;
                                incremented.push({i,j});
                            }
                        }
                    }
                }
            }
        }
    }
    return num_flashes;
}

int main(int argc, char const *argv[])
{
    string line;
    vector<vector<int>> v(10,vector<int>(10,0));
    int row = 0;
    while(cin >> line) {
        for(int col = 0;  col < WIDTH; ++col) v[row][col] = line[col] - '0';
        ++row;
    }    
    
    int step = 1;
    while(true) {
        for(int row = 0; row < HEIGHT; ++row) { for(int col = 0; col < WIDTH; ++col) ++v[row][col]; }
        if(flashes(v) == 100) break;
        ++step;
    }
    cout << step << endl;
    return 0;
}