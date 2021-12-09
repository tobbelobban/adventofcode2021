#include<iostream>
#include<sstream>

using namespace std;

int main(int argc, char const *argv[])
{
    string line, sig_str;
    int counter = 0;
    while(getline(cin,line)) {
        istringstream iss(line);
        getline(iss,line,'|');
        while(iss >> sig_str) {
            cout << sig_str << " ";
            int len = sig_str.length();
            if(len == 2 || len == 3 || len == 4 || len == 7) ++counter;
        }
        cout << endl;
    }
    cout << counter << endl;
    return 0;
}
