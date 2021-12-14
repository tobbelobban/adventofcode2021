#include<iostream>
#include<vector>
#include<algorithm>
#include<limits>

#define STEPS 10
#define ALPHA_SIZE 26

using namespace std;

int main(int argc, char const *argv[])
{
    string sequence, tmp;
    getline(cin,sequence);
    getline(cin,tmp);
    vector<pair<string,char>> m;
    while(getline(cin,tmp)) m.push_back({tmp.substr(0,2), tmp[6]});
    sort(m.begin(), m.end(), 
        [] (const pair<string,char>& p1, const pair<string,char>& p2) {
            return p1.first < p2.first;
        }
    );
    vector<pair<int,int>> split(m.size()+1, {m.size(),m.size()});
    for(unsigned int i = 0; i < m.size(); ++i) {
        const char left = m[i].first[0], right = m[i].first[1], middle = m[i].second;
        for(unsigned int j = 0; j < m.size(); ++j) {
            if(m[j].first[0] == left && m[j].first[1] == middle) {
                split[i].first = j;
            } else if(m[j].first[0] == middle && m[j].first[1] == right) {
                split[i].second = j;
            }
        }
    }
    
    unsigned long c_counters[ALPHA_SIZE];
    fill(begin(c_counters), begin(c_counters)+ALPHA_SIZE,0);
    vector<pair<unsigned long,unsigned long>> change(m.size(), {0,0});
    for(unsigned int i = 0; i < sequence.length() - 1; ++i) {
        c_counters[sequence[i] - 'A'] += 1; 
        for(unsigned int j = 0; j < m.size(); ++j) {
            if(sequence[i] == m[j].first[0] && sequence[i+1] == m[j].first[1]) {
                change[j].first += 1;
            }
        }
    }
    c_counters[sequence[sequence.length()-1] - 'A'] += 1; 
    
    for(unsigned int step = 0; step < STEPS; ++step) {
        for(unsigned int f = 0; f < m.size(); ++f) {
            if(change[f].first) {
                c_counters[m[f].second - 'A'] += change[f].first;
                change[split[f].first].second += change[f].first;
                change[split[f].second].second += change[f].first;
            }
        }
        for(unsigned int f = 0; f < m.size(); ++f) {
            change[f].first = change[f].second;
            change[f].second = 0;
        }
    }
    
    unsigned long max = numeric_limits<unsigned long>::min(), min = numeric_limits<unsigned long>::max();
    for(unsigned int i = 0; i < ALPHA_SIZE; ++i) {
        if(c_counters[i] && c_counters[i] < min) {
            min = c_counters[i];
        }
        if(c_counters[i] > max) {
            max = c_counters[i];
        }
    }
    cout << max - min << endl;
    return 0;
}
