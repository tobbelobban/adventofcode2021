#include<iostream>

#define P1_START 6
#define P2_START 2
#define WIN_CONDITION 1000

// assume board is (0 to 9) + 1
// assume dice is (0 to 99) + 1

using std::cout; using std::endl;

int main(int argc, char const *argv[]) {
    int p1_score = 0, p2_score = 0, p1_pos = P1_START, p2_pos = P2_START, dice = 0, roll = 0, tmp;
    bool is_p1_turn = true;
    while(p1_score < WIN_CONDITION && p2_score < WIN_CONDITION) {
        tmp = (dice % 100 + 1) + ((dice + 1) % 100 + 1) + ((dice + 2) % 100 + 1);
        if(is_p1_turn) {
            tmp += p1_pos;
            p1_pos = (tmp % 10) ? tmp % 10 : 10;
            p1_score += p1_pos;
        } else {
            tmp += p2_pos;
            p2_pos = (tmp % 10) ? tmp % 10 : 10;
            p2_score += p2_pos;
        }
        is_p1_turn = !is_p1_turn;
        dice = (dice + 3) % 100;
        roll += 3;
    }
    cout << (roll * (is_p1_turn ? p1_score : p2_score)) << endl;
    return 0;
}


