#include<iostream>
#include<vector>
#include<cmath>
#include<queue>
#include<unordered_map>

using namespace std;

bool has_beacon(const int scanner_id, int x, int y, int z, const vector<vector<vector<int>>>& scans) {
    for(const auto& beacon : scans[scanner_id]) {
        if(beacon[0] == x && beacon[1] == y && beacon[2] == z) return true;
    }
    return false;
}

bool fit(const int curr, const vector<int>& fitted, vector<vector<vector<int>>>& scans) {
    for(unsigned int ii = 0; ii < fitted.size(); ++ii) {
        int i = fitted[ii];
        for(unsigned int b1 = 0; b1 < scans[i].size(); ++b1) {
            for(unsigned int b2 = 0; b2 < scans[curr].size(); ++b2) {
                for(int x = -1; x < 2; x += 2) {
                    for(int y = -1; y < 2; y += 2) {
                        for(int z = -1; z < 2; z += 2) {
                            for(int j = 0; j < 3; ++j) {
                                for(int k = 0; k < 3; ++k) {
                                    if(k == j) continue;
                                    for(int l = 0; l < 3; ++l) {
                                        if(l == k || l == j) continue;
                                        int x_translate = scans[i][b1][0] - scans[curr][b2][j] * x;
                                        int y_translate = scans[i][b1][1] - scans[curr][b2][k] * y;
                                        int z_translate = scans[i][b1][2] - scans[curr][b2][l] * z;
                                        int counter = 1;
                                        for(unsigned int b3 = 0; b3 < scans[curr].size(); ++b3) {
                                            if(b2 == b3) continue;
                                            if(has_beacon(i, scans[curr][b3][j]*x + x_translate, scans[curr][b3][k]*y+y_translate, scans[curr][b3][l]*z+z_translate, scans)) {
                                                ++counter;
                                            }
                                        }
                                        if(counter >= 12) {
                                            //cout << "MATCH B" << i << " and " << "B" << curr << endl;
                                            for(unsigned int b = 0; b < scans[curr].size(); ++b) {
                                                int new_x = scans[curr][b][j]*x + x_translate;
                                                int new_y = scans[curr][b][k]*y + y_translate;
                                                int new_z = scans[curr][b][l]*z + z_translate;
                                                scans[curr][b][0] = new_x;
                                                scans[curr][b][1] = new_y;
                                                scans[curr][b][2] = new_z;
                                                //cout << new_x << "  " << new_y << "  " << new_z << endl;
                                            }
                                            return true;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return false;
}

int simple_hash(const int x, const int y, const int z) {
    return 100000*x + 1000*y + z; 
}

int main(int argc, char const *argv[]) {
    vector<vector<vector<int>>> scans;
    string coord_str, scanner_id_str;
    queue<int> remaining;
    int counter = 0;
    while(getline(cin,scanner_id_str)) {
        vector<vector<int>> current_scan;
        remaining.push(counter++);
        while(getline(cin, coord_str) && !coord_str.empty()) {
            vector<int> coords;
            int first_comma_pos = coord_str.find(',');
            coords.push_back(stoi(coord_str.substr(0,first_comma_pos)));

            int second_comma_pos = coord_str.find(',', first_comma_pos+1);
            coords.push_back(stoi(coord_str.substr(first_comma_pos+1, second_comma_pos-first_comma_pos)));
            
            coords.push_back(stoi(coord_str.substr(second_comma_pos+1)));
            current_scan.push_back(coords);
        }
        scans.push_back(current_scan);
    }
    vector<int> fitted = {0};
    remaining.pop();
    --counter;
    while(counter) {
        const int curr = remaining.front();
        remaining.pop();
        if(fit(curr, fitted, scans)) {
            fitted.push_back(curr);
            --counter;
        } else {
            remaining.push(curr);
        }
        cout << counter << endl;
    }
    unordered_map<int,int> beacon_counts;
    counter = 0;
    for(unsigned int s = 0; s < scans.size(); ++s) {
        for(const auto& b : scans[s]) {
            const int b_hash = simple_hash(b[0], b[1], b[2]);
            if(beacon_counts.find(b_hash) != beacon_counts.end()) {
                beacon_counts[b_hash] += 1;
            } else {
                beacon_counts.insert({b_hash,1});
                ++counter;
            }
        }
    }
    cout << counter << endl;
    return 0;
}
