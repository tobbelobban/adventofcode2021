#include<iostream>
#include<vector>
#include<numeric>

using namespace std;

int main(int argc, char const *argv[])
{
    vector<int> fish(9,0);
    string line;
    while(getline(cin,line,',')) ++fish[stoi(line)];
    int upper, lower;
    for(int i = 0; i < 80; ++i) {
        upper = fish[0];
        for(int j = 7; j > 0; --j) {
            lower = fish[j-1];
            fish[j-1] = upper;
            upper = lower;
        }
        fish[6] += fish[7];
        fish[7] = fish[8];
        fish[8] = upper;
    }
    cout << accumulate(fish.begin(), fish.end(), 0) << endl;
    return 0;
}
