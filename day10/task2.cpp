#include<algorithm>
#include<iostream>
#include<stack>
#include<vector>

using namespace std;

typedef unsigned long bignum;

const string openers = "({[<";

bignum verify_line(const string& line) {
    stack<char> char_stack;
    char_stack.push(line[0]);
    int pos = 1;
    while(pos < line.length()) {
        const char& next_c = line[pos];
        if(openers.find(next_c) != string::npos) {
            char_stack.push(next_c);
        } else {
            const char& c_open = char_stack.top(); char_stack.pop();
            if(c_open == '(' &&  next_c != ')') return 0;
            if(c_open == '{' &&  next_c != '}') return 0;
            if(c_open == '[' &&  next_c != ']') return 0;
            if(c_open == '<' &&  next_c != '>') return 0;
        }
        ++pos;
    }
    bignum score = 0;
    while(!char_stack.empty()) {
        const char& c_open = char_stack.top(); char_stack.pop();
        score *= 5;
        if(c_open == '(') {
            score += 1;
        } else if(c_open == '{') {
            score += 3;
        } else if(c_open == '[') {
            score += 2;
        } else if(c_open == '<'){
            score += 4;
        }
    }
    return score;
}

int main(int argc, char const *argv[])
{
    string line;
    vector<bignum> scores;
    bignum res;
    while(cin >> line) {
        res = verify_line(line);
        if(res) scores.push_back(res);
    }
    sort(scores.begin(), scores.end());
    cout << scores[scores.size()/2] << endl;
    return 0;
}