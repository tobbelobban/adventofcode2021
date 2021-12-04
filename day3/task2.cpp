#include<iostream>
#include<vector>

using namespace std;

int main(int argc, char const *argv[])
{
    vector<string> nums;
    string line;
    int i = 0;
    while(cin >> line) {
        nums.push_back(line);        
        ++i;
    }
    int majors[i];
    fill_n(majors,i,1);
    int minors[i];
    fill_n(minors,i,1);
    for(i = 0; i < nums[0].length(); ++i) {
        int count_major_ones = 0, total_majors = 0, count_minor_ones = 0, total_minors = 0;
        for(int j = 0; j < nums.size(); ++j) {
            if(majors[j]) {
                ++total_majors;
                if(nums[j][i] == '1') ++count_major_ones;
            }
            if(minors[j]) {
                ++total_minors;
                if(nums[j][i] == '1') ++count_minor_ones;
            }
        }
        const char major_char = (count_major_ones * 2 > total_majors ? '1' : (count_major_ones * 2 < total_majors ? '0' : '1'));
        const char minor_char = (count_minor_ones * 2 < total_minors ? '1' : (count_minor_ones * 2 > total_minors ? '0' : '0')); 
        for(int j = 0; j < nums.size(); ++j) {
            if(total_majors > 1 && majors[j]) {
                if(!(nums[j][i] == major_char)) {
                    majors[j] = 0;
                }
            }
            if(total_minors > 1 && minors[j]) {
                if(!(nums[j][i] == minor_char)) {
                    minors[j] = 0;
                }
            }
        }
    }
    int major_i, minor_i;
    for(i = 0; i < nums.size(); ++i) {
        if(majors[i]) {
            major_i = i; 
        }
        if(minors[i]) {
          minor_i = i;
        } 
    }
    int major = 0, minor = 0;
    for(i = 0; i < nums[0].length(); ++i) {
        major <<= 1;
        minor <<= 1;
        if(nums[major_i][i] == '1') {
            major |= 0x1;
        } 
        if(nums[minor_i][i] == '1') {
            minor |= 0x1;
        } 
        
    }
    cout << major * minor << endl;
    return 0;
}
