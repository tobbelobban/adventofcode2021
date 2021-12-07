#include<iostream>
#include<unordered_map>
#include<algorithm>
#include<vector>
#include<numeric>
#include<cmath>

using namespace std;

int main(int argc, char const *argv[])
{   
    unordered_map<int,int> m;
    string next_pos;
    int val, min_val = numeric_limits<int>::max(), max_val = numeric_limits<int>::min();
    while(getline(cin,next_pos,',')) {
        val = stoi(next_pos);
        if(val < min_val) {
            min_val = val;
        } else if(val > max_val) {
            max_val = val;
        }
        if(m.find(val) != m.end()) {
            ++m[val];
        } else {
            m.insert({val,1});
        }
    }
    int cost = numeric_limits<int>::max(), new_cost, h_pos_target;
    for(int h_pos_target = min_val; h_pos_target < max_val; ++h_pos_target) {
        new_cost = 0;
        for(auto iter = m.begin(); iter != m.end(); ++iter) new_cost += abs(iter->first - h_pos_target) * iter->second;
        if(new_cost > cost) break;
        if(new_cost < cost) cost = new_cost;
    }
    cout << cost << endl;
    return 0;
}
