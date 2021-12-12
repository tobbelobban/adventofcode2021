#include<iostream>
#include<unordered_map>
#include<vector>
#include<queue>

using namespace std;

int count_paths(const string& curr, unordered_map<string,vector<string>>& m, unordered_map<string,int>& remaining) {
    if(curr == "end") return 1;
    int res = 0;
    for(string& next : m[curr]) {
        if(!remaining[next]) continue;
        if(!isupper(next[0])) --remaining[next];
        res += count_paths(next, m, remaining);
        ++remaining[next];
    }
    return res;
}

int main(int argc, char const *argv[])
{
    unordered_map<string,vector<string>> m;
    unordered_map<string,int> remaining;
    string from, to;
    while(getline(cin,from,'-')) {
        getline(cin,to);
        if(m.find(from) != m.end()) {
            m[from].push_back(to);
        } else {
            m.insert({from,{to}});
            remaining.insert({from,1});
        }
        if(m.find(to) != m.end()) {
            m[to].push_back(from);
        } else {
            m.insert({to,{from}});
            remaining.insert({to,1});
        }
    }    
    remaining["start"] = 0;
    int base = count_paths("start", m, remaining), ans = base;
    for(auto iter = remaining.begin(); iter != remaining.end(); ++iter) {
        if(!(isupper(iter->first[0]) || iter->first == "start" || iter->first == "end")) {
            ++(remaining[iter->first]);
            ans += count_paths("start", m, remaining) - base;
            --(remaining[iter->first]);
        }
    }
    cout << ans << endl;
    return 0;
}
