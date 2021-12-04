#include<iostream>

using namespace std;

int main(int argc, char const *argv[])
{
    int depth = 0, h_pos = 0;
    string cmd;
    int val;
    while(cin >> cmd >> val) {
        if(cmd == "up") {
            depth -= val;
        } else if(cmd == "down") {
            depth += val;
        } else if(cmd == "forward") {
            h_pos += val;
        } else {
            cout << "UNKNOWN COMMAND: " << cmd;
        }
    }
    cout << h_pos * depth << endl;
    return 0;
}
