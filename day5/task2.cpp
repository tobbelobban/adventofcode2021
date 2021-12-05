#include<iostream>
#include<sstream>
#include<vector>

using namespace std;

int main(int argc, char const *argv[])
{
    vector<vector<int>> field(1000,vector<int>(1000,0));
    string line, x1_str, y1_str, x2_str, y2_str, arrow;
    int x1, y1, x2, y2;
    int row = 0;
    while(getline(cin,line)) {
        istringstream iss(line);
        getline(iss,x1_str,',');
        getline(iss,y1_str,' ');
        getline(iss,arrow,' ');
        getline(iss,x2_str,',');
        getline(iss,y2_str);
        x1 = stoi(x1_str); y1 = stoi(y1_str);
        x2 = stoi(x2_str); y2 = stoi(y2_str);
        if(x1 == x2) {
            int from_y = y1, to_y = y2;
            if(from_y > to_y) {
                from_y = to_y;
                to_y = y1;
            }
            while(from_y <= to_y) {
                ++field[x1][from_y++];
            }
        } else if(y1 == y2) {
            int from_x = x1, to_x = x2;
            if(from_x > to_x) {
                from_x = to_x;
                to_x = x1;
            }
            while(from_x <= to_x) {
                ++field[from_x++][y1];
            }
        } else if(x1 < x2 && y1 < y2) {
            while(x1 <= x2) {
                ++field[x1++][y1++];
            }
        } else if(x1 > x2 && y1 > y2) {
            while(x2 <= x1) {
                ++field[x2++][y2++];
            }
        } else if(x1 < x2 && y1 > y2) {
            while(y2 <= y1) {
                ++field[x2--][y2++];
            }
        } else if(x1 > x2 && y1 < y2) {
            while(y1 <= y2) {
                ++field[x1--][y1++];
            }
        }
    }
    int counter = 0;
    for(int i = 0; i < 1000; ++i) {
        for(int j = 0; j < 1000; ++j) {
            if(field[i][j] > 1) ++counter;
        }
    }
    cout << counter << endl;
    return 0;
}

