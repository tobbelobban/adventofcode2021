#include<iostream>
#include<cmath>
#include<vector>
#include<chrono>
#include<numeric>

using namespace std;

int fuel_cost(const int& dist) {
    return (dist + 1) * dist / 2;
}

int main(int argc, char const *argv[])
{   
    auto start = chrono::steady_clock::now();
    string next_pos;
    vector<int> v;
    int val, min = numeric_limits<int>::max(), max = numeric_limits<int>::min();
    while(getline(cin,next_pos,',')) {
        val = stoi(next_pos);
        v.push_back(val);
        if(val > max) {
            max = val;
        } else if(val < min) {
            min = val;
        }
    }
    int cost = numeric_limits<int>::max(), new_cost;
    for(int zero_pos = min; zero_pos < max; ++zero_pos) {
        new_cost = 0;
        for(const int& i : v) new_cost += fuel_cost(abs(i - zero_pos));
        if(new_cost < cost) cost = new_cost;
    }
    
    auto end = chrono::steady_clock::now();
    cout << "Time: " << chrono::duration_cast<chrono::microseconds>(end-start).count() << " micros" << endl;
    std::cout << "Answer: " << cost << endl;
    return 0;
}
