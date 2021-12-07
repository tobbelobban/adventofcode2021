#include<iostream>
#include<unordered_map>
#include<vector>
#include<numeric>
#include<cmath>
#include<algorithm>
#include<chrono>

using namespace std;

int main(int argc, char const *argv[])
{   
    auto start = chrono::steady_clock::now();
    unordered_map<int,int> m;
    vector<int> v;
    string next_pos;
    int val;
    while(getline(cin,next_pos,',')) {
        val = stoi(next_pos);
        v.push_back(val);
        if(m.find(val) != m.end()) {
            ++m[val];
        } else {
            m.insert({val,1});
        }
    }
    sort(v.begin(), v.end());
    int cost = 0, init_guess = ((v.size() % 2) == 0) ? v[v.size()/2] : v[v.size()/2] + v[v.size()/2 - 1]/2;
    for(auto iter = m.begin(); iter != m.end(); ++iter) cost += abs(iter->first - init_guess) * iter->second;
    auto end = chrono::steady_clock::now();
    cout << "Time: " << chrono::duration_cast<chrono::microseconds>(end-start).count() << " ms" << endl;
    std::cout << cost << endl;
    return 0;
}
