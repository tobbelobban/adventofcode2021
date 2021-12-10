
#include<iostream>
#include<stack>

using namespace std;

const string openers = "({[<";

int verify_line(const string& line) {
    stack<char> char_stack;
    char_stack.push(line.at(0));
    int pos = 1;
    while(!char_stack.empty()) {
        if(pos == line.length()) return 0; // incomplete or end
        if(openers.find(line[pos]) != string::npos) {
            char_stack.push(line[pos]);
        } else {
            const char& c_open = char_stack.top(); char_stack.pop();
            const char& c_close = line[pos];
            if(c_open != '(' &&  c_close == ')') return 3;
            if(c_open != '{' &&  c_close == '}') return 1197;
            if(c_open != '[' &&  c_close == ']') return 57;
            if(c_open != '<' &&  c_close == '>') return 25137;
        }
        ++pos;
    }
    return 0;
}

int main(int argc, char const *argv[])
{
    string line;
    int ans = 0;
    while(cin >> line) ans += verify_line(line);        
    cout << ans << endl;
    return 0;
}
