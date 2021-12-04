#include<iostream>

using namespace std;

int main(int argc, char const *argv[])
{
    unsigned int counter = 0;
    int prev_depth, depth, next_depth, next_next_depth, sum;
    cin >> prev_depth >> depth >> next_depth;
    sum = depth + next_depth;
    while(cin >> next_next_depth) {
        if(sum + next_next_depth > sum + prev_depth) ++counter;
        sum = sum - depth + next_next_depth;
        prev_depth = depth;
        depth = next_depth;
        next_depth = next_next_depth;

    }
    cout << counter <<  endl;
    return 0;
}
