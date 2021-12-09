#include<iostream>
#include<sstream>
#include<algorithm>
#include<vector>
#include<cmath>

using namespace std;

int str_has_char(const string& str, const char c) {
    int i;
    for(i = 0; i < str.length(); ++i) {
        if(str.at(i) == c) return i;
    }
    return i;
}

int main(int argc, char const *argv[])
{
    string line, sig_str;
    int counter = 0;        //   a b c d e f g
    const int combos[10][7] = { {1,1,1,0,1,1,1},
                                {0,0,1,0,0,1,0},
                                {1,0,1,1,1,0,1},
                                {1,0,1,1,0,1,1},
                                {0,1,1,1,0,1,0},
                                {1,1,0,1,0,1,1},
                                {1,1,0,1,1,1,1},
                                {1,0,1,0,0,1,0},
                                {1,1,1,1,1,1,1},
                                {1,1,1,1,0,1,1} };
    while(getline(cin,line, '|')) {
        istringstream iss(line);
        int curr = 0, len;
        vector<pair<int,vector<int>>> v(10,{0,vector<int>(7,0)});
        while(iss >> sig_str) {
            len = 0;
            for(const char& c : sig_str) {
                if(c == 'a') {
                    v[curr].second[0] = 1;
                } else if(c == 'b') {
                    v[curr].second[1] = 1;
                } else if(c == 'c') {
                    v[curr].second[2] = 1;
                } else if(c == 'd') {
                    v[curr].second[3] = 1;
                } else if(c == 'e') {
                    v[curr].second[4] = 1;
                } else if(c == 'f') {
                    v[curr].second[5] = 1;
                } else if(c == 'g'){
                    v[curr].second[6] = 1;
                }
                ++len;
            }
            v[curr].first = len;
            ++curr;
        }
        sort(v.begin(), v.end(), [](const pair<int,vector<int>>& p1, const pair<int,vector<int>>& p2) {return p1.first < p2.first;});
        int one_i1 = -1, one_i2, remain_i1 = -1, remain_i2;
        int map[7];
        std::fill(map,map+7,-1);
        for(int i = 0; i < 7; ++i) {
            if(v[0].second[i]) {
                if(one_i1 > -1) {
                    one_i2 = i;
                    break;
                } else {
                    one_i1 = i;
                }
            }
        }
        int six_index = (v[6].second[one_i1] && v[6].second[one_i2] ? (v[7].second[one_i1] && v[7].second[one_i2] ? 8 : 7) : 6);
        int three_index = (v[3].second[one_i1] && v[3].second[one_i2] ? 3 : (v[4].second[one_i1] && v[4].second[one_i2] ? 4 : 5));

        for(int i = 0; i < 7; ++i) {
            if(v[0].second[i] != v[1].second[i]) {
                map[i] = 0; 
            }
        }
        //map[2] = (v[six_index].second[one_i1] ? one_i2 : one_i1);
        map[v[six_index].second[one_i1] ? one_i2 : one_i1] = 2;
        //map[5] = (map[2] == one_i1 ? one_i2 : one_i1);
        map[map[one_i1] == 2 ? one_i2 : one_i1] = 5;
        int missing_3_1 = -1, missing_3_2;
        for(int i = 0; i < 7; ++i) {
            if(!v[three_index].second[i]) {
                if(missing_3_1 > -1) {
                    missing_3_2 = i;
                } else {
                    missing_3_1 = i;
                }
            }
        }
        if(v[2].second[missing_3_1]) {
            //map[1] = missing_3_1;
            map[missing_3_1] = 1;
            //map[4] = missing_3_2;
            map[missing_3_2] = 4;
        } else {
            //map[1] = missing_3_2;
            map[missing_3_2] = 1;
            //map[4] = missing_3_1;
            map[missing_3_1] = 4;

        }
        for(int i = 0; i < 7; ++i) {
            if(map[i] == -1) {
                if(remain_i1 > -1) {
                    remain_i2 = i;
                    break;
                } 
                remain_i1 = i;
            }
        }
        if(v[2].second[remain_i1]) {
            map[remain_i2] = 6;
            map[remain_i1] = 3;
        } else {
            map[remain_i1] = 6;
            map[remain_i2] = 3;
        }
        getline(cin,line);
        istringstream iss2(line);
        int i = 3;
        while(iss2 >> sig_str) {
            int tmp_v[7];
            std::fill(tmp_v, tmp_v+7,0);
            for(const char& c : sig_str) {
                if(c == 'a') {
                    tmp_v[map[0]] = 1;
                } else if(c == 'b') {
                    tmp_v[map[1]] = 1;
                } else if(c == 'c') {
                    tmp_v[map[2]] = 1;
                } else if(c == 'd') {
                    tmp_v[map[3]] = 1;
                } else if(c == 'e') {
                    tmp_v[map[4]] = 1;
                } else if(c == 'f') {
                    tmp_v[map[5]] = 1;
                } else if(c == 'g'){
                    tmp_v[map[6]] = 1;
                }
            }
            for(int k = 0; k < 10; ++k) {
                bool verified = true;
                for(int j = 0; j < 7; ++j) {
                    if(tmp_v[j] != combos[k][j]) {
                        verified = false;
                        break;
                    }
                }
                if(verified) {
                    counter += k * pow(10,i--);
                }
            }
        }
    }   
    cout << "Result: " << counter << endl;
    char letters[128] = {};
    letters[0b11] = 80;
    cout << letters[0b1'1] << endl;
    return 0;
}