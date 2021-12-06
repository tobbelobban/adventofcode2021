#include<iostream>
#include<vector>

using namespace std;

int main(int argc, char const *argv[])
{
    vector<unsigned long> fish(9,0);
    unsigned long val;
    string line;
    while(getline(cin,line,',')) {
        val = stoul(line);
        ++fish[val];
    }
    unsigned long upper, lower;
    for(int i = 0; i < 256; ++i) {
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
    for(unsigned long f : fish) val += f;
    cout << val << endl;
    return 0;
}
