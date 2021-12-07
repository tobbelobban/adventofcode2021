#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>
#include<chrono>

using namespace std;

int main(int argc, char const *argv[])
{   
    auto start = chrono::steady_clock::now();
    vector<int> v;
    string next_pos;
    int val, n;
    while(getline(cin,next_pos,',')) v.push_back(stoi(next_pos));
    n = v.size();
    sort(v.begin(), v.end());
    int cost = 0, init_guess = ((v.size() % 2) == 0) ? v[n/2] : v[n/2] + v[n/2 - 1]/2;
    for(const int& i : v) cost += abs(i - init_guess);
    auto end = chrono::steady_clock::now();
    cout << "Time: " << chrono::duration_cast<chrono::microseconds>(end-start).count() << " micros" << endl;
    std::cout << "Answer: " << cost << endl;
    return 0;
}
