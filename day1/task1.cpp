#include<iostream>

using namespace std;

int main(int argc, char const *argv[])
{
    unsigned int counter = 0;
    int prev_depth, depth;
    cin >> prev_depth;
    while(cin >> depth) {
        if(depth > prev_depth) ++counter;
        prev_depth = depth;
    }
    cout << counter <<  endl;
    return 0;
}
