
// r1:                      1                           2                           3
// r2:               1      2       3           1       2       3           1       2       3
// r3:             1 2 3  1 2 3   1 2 3       1 2 3   1 2 3   1 2 3       1 2 3   1 2 3   1 2 3  
// ----------------------------------------------------------------------------------------------
// sum:            3 4 5  4 5 6   5 6 7       4 5 6   5 6 7   6 7 8       5 6 7   6 7 8   7 8 9

// occurrences:
//  0: 0
//  1: 0
//  2: 0
//  3: 1
//  4: 3
//  5: 6
//  6: 7
//  7: 6
//  8: 3
//  9: 1 
// 10: 0

#include<iostream>

#define P1_START 6
#define P2_START 2
#define TARGET 21

typedef unsigned long long bignum;

using std::cout; using std::endl;

constexpr int occ_v[] = {0, 0, 0, 1, 3, 6, 7, 6, 3, 1, 0};

void count_wins(int p1_pos, int p2_pos, int p1_score, int p2_score, bignum paths, bignum * wins, bool is_p1) {
    if(is_p1) {
        for(int i = 3; i < 10; ++i) {
            int tmp_pos = (p1_pos + i);
            tmp_pos = (tmp_pos % 10) ? tmp_pos % 10 : 10;
            if(p1_score + tmp_pos >= TARGET) {
                *wins += occ_v[i] * paths;
            } else {
                count_wins(tmp_pos, p2_pos, p1_score + tmp_pos, p2_score, paths * occ_v[i], wins, !is_p1);
            }        
        }
    } else {
        for(int i = 3; i < 10; ++i) {
            int tmp_pos = (p2_pos + i);
            tmp_pos = (tmp_pos % 10) ? tmp_pos % 10 : 10;
            if(p2_score + tmp_pos >= TARGET) {
                *(wins + 1) += occ_v[i] * paths;
            } else {
                count_wins(p1_pos, tmp_pos, p1_score, p2_score + tmp_pos, paths * occ_v[i], wins, !is_p1);
            }
        }
    }
}

int main() {
    bignum wins[] = {0, 0};
    count_wins(P1_START, P2_START, 0, 0, 1, wins, true);
    cout << "P1 #wins = \t" << wins[0]
            << "\nP2 #wins = \t" << wins[1] << endl;
}
