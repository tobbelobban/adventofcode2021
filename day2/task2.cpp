#include<iostream>

using namespace std;

int main(int argc, char const *argv[])
{
    int depth = 0, h_pos = 0, aim = 0;
    string cmd;
    int val;
    while(cin >> cmd >> val) {
        if(cmd == "up") {
            aim -= val;
        } else if(cmd == "down") {
            aim += val;
        } else if(cmd == "forward") {
            h_pos += val;
            depth += aim * val;
        } else {
            cout << "UNKNOWN COMMAND: " << cmd;
        }
    }
    cout << h_pos * depth << endl;
    return 0;
}
