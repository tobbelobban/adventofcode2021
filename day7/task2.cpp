#include<iostream>
#include<cmath>
#include<vector>
#include<chrono>

using namespace std;

int fuel_cost(const int& dist) {
    return (dist + 1) * dist / 2;
}

int main(int argc, char const *argv[])
{   
    auto start = chrono::steady_clock::now();
    string next_pos;
    vector<int> v;
    int val, init_guess = 0, n = 0;
    while(getline(cin,next_pos,',')) {
        val = stoi(next_pos);
        init_guess += val;
        v.push_back(val);
    }
    n = v.size();
    int cost = 0;
    init_guess = floor((double)init_guess/n);
    for(const int& i : v) cost += fuel_cost(abs(i - init_guess));
    auto end = chrono::steady_clock::now();
    cout << "Time: " << chrono::duration_cast<chrono::microseconds>(end-start).count() << " micros" << endl;
    std::cout << "Answer: " << cost << endl;
    return 0;
}
