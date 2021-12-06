#include<iostream>
#include<vector>

using namespace std;

int main(int argc, char const *argv[])
{
    vector<int> fish(9,0);
    int val;
    string line;
    while(getline(cin,line,',')) {
        val = stoi(line);
        ++fish[val];
    }
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
    val = 0;
    for(int f : fish) val += f;
    cout << val << endl;
    return 0;
}
