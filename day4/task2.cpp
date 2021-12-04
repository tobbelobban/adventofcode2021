#include<iostream>
#include<sstream>
#include<vector>

using namespace std;

bool check_board_win(const vector<int>& boards, const vector<int>& marked, const int board_num) {
    int begin = board_num * 25;
    int end = begin + 25;
    if(begin >= boards.size() || end >= boards.size()) return false;
    int res = 0;
    for(int i = begin; i < end; ++i) {
        if(i % 5 == 0) res = 0;
        if(marked[i]) ++res;
        if(res == 5) return true;
    }
    for(int col_start = begin; col_start < begin+5; ++col_start) {
        res = 0;
        for(int i = col_start; i < col_start+25; i += 5) {
            if(marked[i]) ++res;
            if(res == 5) return true;
        }
    }
    return false;
}
int main(int argc, char const *argv[])
{
    string line;
    getline(cin, line);
    stringstream ss(line);
    vector<int> numbers, boards;
    string num_str;
    while(getline(ss,num_str,',')) numbers.push_back(stoi(num_str));
    int num;
    while(cin >> num) boards.push_back(num);
    constexpr int board_size = 25;
    const int all_boards_size = boards.size();
    const int num_boards = all_boards_size / board_size;
    vector<int> marked(all_boards_size, 0);
    vector<int> has_won(num_boards, 0);
    int last_winning_board = -1, last_num;
    int remaining_boards = num_boards;
    for(int n : numbers) {
        for(int i = 0; i < all_boards_size; ++i) {
            if(boards[i] == n) marked[i] = 1;
        }
        for(int j = 0; j < num_boards; ++j) {
            if(check_board_win(boards, marked, j) && !has_won[j]) {
                --remaining_boards;
                has_won[j] = 1;
                if(remaining_boards == 1) {
                    last_winning_board = j;
                    last_num = n;
                    break;
                }
            }
        }
        if(last_winning_board > -1) break;
    }
    int begin = board_size * last_winning_board;
    int end = begin + board_size;
    int unmarked_sum = 0;
    for(int i = begin; i < end; ++i) {
        if(!marked[i]) unmarked_sum += boards[i];
    }
    cout <<  unmarked_sum * last_num << endl;
    return 0;
}
