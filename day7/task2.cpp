#include<iostream>
#include<unordered_map>
#include<numeric>
#include<cmath>
#include<algorithm>
#include<chrono>

using namespace std;

int fuel_cost(const int& dist) {
    return (dist + 1) * dist / 2;
}

int main(int argc, char const *argv[])
{   
    auto start = chrono::steady_clock::now();
    unordered_map<int,int> m;
    string next_pos;
    int val, init_guess = 0, n = 0;
    while(getline(cin,next_pos,',')) {
        val = stoi(next_pos);
        init_guess += val;
        if(m.find(val) != m.end()) {
            ++m[val];
        } else {
            m.insert({val,1});
        }
        ++n;
    }
    int cost = 0;
    init_guess = floor((double)init_guess/n);
    for(auto iter = m.begin(); iter != m.end(); ++iter) cost += fuel_cost(abs(iter->first - init_guess)) * iter->second;
    auto end = chrono::steady_clock::now();
    cout << "Time: " << chrono::duration_cast<chrono::milliseconds>(end-start).count() << " ms" << endl;
    std::cout << cost << endl;
    return 0;
}
