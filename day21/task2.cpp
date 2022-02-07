
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
#include<chrono>

#define P1_START 6
#define P2_START 2
#define TARGET 21

typedef unsigned long long bignum;

using namespace std::chrono;
using std::cout; using std::endl; 


constexpr int occ_v[] = {0, 0, 0, 1, 3, 6, 7, 6, 3, 1, 0};

void count_wins(int* pos, int* scores, bignum paths, bignum* wins, int curr) {
    int new_pos, tmp_pos;
    for(int i = 3; i < 10; ++i) {
        new_pos = (*(pos+curr) + i) % 10;
        new_pos = new_pos ? new_pos : 10;
        if(*(scores+curr) + new_pos >= TARGET) {
            *(wins+curr) += *(occ_v+i) * paths;
        } else {
            tmp_pos = *(pos+curr);
            *(pos+curr) = new_pos;
            *(scores+curr) += new_pos;
            count_wins(pos, scores, paths * *(occ_v+i), wins, curr ? 0 : 1);
            *(pos+curr) = tmp_pos;
            *(scores+curr) -= new_pos;
        }        
    }
}

int main() {
    auto start = high_resolution_clock::now();

    int positions[] = {P1_START, P2_START};
    int scores[] = {0,0};
    bignum wins[] = {0, 0};

    count_wins(positions, scores, 1, wins, 0);

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    cout << "P1 #wins = \t" << wins[0]
            << "\nP2 #wins = \t" << wins[1] <<
                "\nTime (ms): \t" << duration.count() << endl;
}
