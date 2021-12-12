#include<iostream>
#include<unordered_map>
#include<vector>
#include<queue>

using namespace std;

int count_paths(const string& curr, unordered_map<string,vector<string>>& m, unordered_map<string,int>& visited) {
    if(curr == "end") return 1;
    int res = 0;
    for(string& next : m[curr]) {
        if(visited[next]) continue;
        if(!(isupper(next[0]) || visited[next])) visited[next] = 1;
        res += count_paths(next, m, visited);
        visited[next] = 0;
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
    cout << count_paths("start", m, visited) << endl;
    return 0;
}
