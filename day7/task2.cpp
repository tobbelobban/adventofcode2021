#include<iostream>
#include<unordered_map>
#include<vector>
#include<numeric>
#include<cmath>
#include<algorithm>

using namespace std;

int fuel_cost(const int& dist) {
    return (dist + 1) * dist / 2;
}

int main(int argc, char const *argv[])
{   
    unordered_map<int,int> m;
    vector<int> v;
    string next_pos;
    int val, init_guess = 0;
    while(getline(cin,next_pos,',')) {
        val = stoi(next_pos);
        init_guess += val;
        v.push_back(val);
        if(m.find(val) != m.end()) {
            ++m[val];
        } else {
            m.insert({val,1});
        }
    }
    sort(v.begin(), v.end());
    int cost = 0;
    init_guess = floor((double)init_guess/v.size());
    for(auto iter = m.begin(); iter != m.end(); ++iter) cost += fuel_cost(abs(iter->first - init_guess)) * iter->second;
    std::cout << cost << endl;
    return 0;
}
