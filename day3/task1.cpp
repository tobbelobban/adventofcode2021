#include<iostream>

using namespace std;

int main(int argc, char const *argv[])
{
    int num_lines = 0;
    int ones[12]{0};
    string line;
    int i;
    while(cin >> line) {
        i = 0;
        for(char c : line) {
            if(c == '1') {
                ones[i] += 1;
            }
            ++i;
        }   
        ++num_lines;
    }
    
    int gamma = 0, eps = 0;
    for(int j = 0; j < i; ++j) {
        if(ones[j] * 2 > num_lines) {
            gamma <<= 1;
            gamma |= 0x1;
            eps <<= 1;
        } else {
            gamma <<= 1;
            eps <<= 1;
            eps |= 0x1;
        }
    }
    cout << t<<endl;
    cout << gamma * eps << endl;
    return 0;
}
