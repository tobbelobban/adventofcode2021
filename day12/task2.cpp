#include<iostream>
#include<unordered_map>
#include<vector>
#include<queue>

using namespace std;

int count_paths(const string& curr, unordered_map<string,vector<string>>& m, unordered_map<string,int>& visited, const bool& repeat = false) {
    if(curr == "end") return 1;
    int res = 0;
    for(string& next : m[curr]) {
        if(next == "start") {
            continue;
        } else if(isupper(next[0])) {
            res += count_paths(next, m, visited, repeat);
        } else if(repeat && visited[next] == 1) {
            ++visited[next];
            res += count_paths(next, m, visited, false);
            --visited[next];
        } else if(!visited[next]){
            ++visited[next];
            res += count_paths(next, m, visited, repeat);
            --visited[next];
        }
    }
    return res;
}

int main(int argc, char const *argv[])
{
    unordered_map<string,vector<string>> m;
    unordered_map<string,int> visited;
    string from, to;
    while(getline(cin,from,'-')) {
        getline(cin,to);
        if(m.find(from) != m.end()) {
            m[from].push_back(to);
        } else {
            m.insert({from,{to}});
            visited.insert({from,0});
        }
        if(m.find(to) != m.end()) {
            m[to].push_back(from);
        } else {
            m.insert({to,{from}});
            visited.insert({to,0});
        }
    }    
    visited["start"] = 1;
    cout << count_paths("start", m, visited, true) << endl;
    return 0;
}
