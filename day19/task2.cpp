#include<iostream>
#include<vector>
#include<cmath>
#include<queue>
#include<unordered_map>

#define NUM_ROTS 24

using namespace std;

const int rotation_matrices[24][3][3] = {   
    {{ 1, 0, 0}, { 0, 1, 0}, { 0, 0, 1}}, 
    {{ 1, 0, 0}, { 0, 0,-1}, { 0, 1, 0}}, 
    {{ 1, 0, 0}, { 0,-1, 0}, { 0, 0,-1}}, 
    {{ 1, 0, 0}, { 0, 0, 1}, { 0,-1, 0}}, 

    {{ 0, 1, 0}, {-1, 0, 0}, { 0, 0, 1}}, 
    {{ 0, 1, 0}, { 0, 0,-1}, {-1, 0, 0}}, 
    {{ 0, 1, 0}, { 1, 0, 0}, { 0, 0,-1}}, 
    {{ 0, 1, 0}, { 0, 0, 1}, { 1, 0, 0}}, 

    {{ 0, 0, 1}, { 0, 1, 0}, {-1, 0, 0}}, 
    {{ 0, 0, 1}, {-1, 0, 0}, { 0,-1, 0}}, 
    {{ 0, 0, 1}, { 0,-1, 0}, { 1, 0, 0}}, 
    {{ 0, 0, 1}, { 1, 0, 0}, { 0, 1, 0}}, 

    {{-1, 0, 0}, { 0,-1, 0}, { 0, 0, 1}}, 
    {{-1, 0, 0}, { 0, 0,-1}, { 0,-1, 0}}, 
    {{-1, 0, 0}, { 0, 1, 0}, { 0, 0,-1}}, 
    {{-1, 0, 0}, { 0, 0, 1}, { 0, 1, 0}}, 

    {{ 0,-1, 0}, { 1, 0, 0}, { 0, 0, 1}}, 
    {{ 0,-1, 0}, { 0, 0,-1}, { 1, 0, 0}}, 
    {{ 0,-1, 0}, {-1, 0, 0}, { 0, 0,-1}}, 
    {{ 0,-1, 0}, { 0, 0, 1}, {-1, 0, 0}}, 

    {{ 0, 0,-1}, { 0, 1, 0}, { 1, 0, 0}}, 
    {{ 0, 0,-1}, {-1, 0, 0}, { 0, 1, 0}}, 
    {{ 0, 0,-1}, { 0,-1, 0}, {-1, 0, 0}}, 
    {{ 0, 0,-1}, { 1, 0, 0}, { 0,-1, 0}}
};

void rotate(vector<int>& pos, const int rot_id) {
    const int* r1_ptr = &rotation_matrices[rot_id][0][0];
    const int* r2_ptr = &rotation_matrices[rot_id][1][0];
    const int* r3_ptr = &rotation_matrices[rot_id][2][0];
    const int new_x = *(r1_ptr+0) * pos[0] + *(r1_ptr+1) * pos[1] + *(r1_ptr+2) * pos[2];
    const int new_y = *(r2_ptr+0) * pos[0] + *(r2_ptr+1) * pos[1] + *(r2_ptr+2) * pos[2];
    const int new_z = *(r3_ptr+0) * pos[0] + *(r3_ptr+1) * pos[1] + *(r3_ptr+2) * pos[2];
    pos[0] = new_x;
    pos[1] = new_y;
    pos[2] = new_z;
}

void translate(vector<int>& pos, const vector<int>& d) {
    pos[0] += d[0];
    pos[1] += d[1];
    pos[2] += d[2];
}

bool has_beacon(const int scanner_id, const vector<int>& b_curr, const vector<vector<vector<int>>>& scans) {
    for(const vector<int>& beacon : scans[scanner_id]) {
        if( beacon[0] == b_curr[0] && 
            beacon[1] == b_curr[1] && 
            beacon[2] == b_curr[2]  ) 
            return true;
    }
    return false;
}

bool new_fit(const int curr, const vector<int>& fitted, vector<vector<vector<int>>>& scans, vector<vector<int>>& tested, vector<vector<int>>& scanner_positions) {
    for(const int& i : fitted) {
        if(tested[curr][i]) continue;
        tested[curr][i] = 1;
        for(const vector<int>& b_i : scans[i]) {
            for(unsigned int i1_curr = 0; i1_curr < scans[curr].size(); ++i1_curr) {
                for(int rot = 0; rot < NUM_ROTS; ++rot) {
                    vector<int> b1_curr = scans[curr][i1_curr];
                    vector<vector<int>> updated_beacons(scans[curr].size(), vector<int>(3,0));
                    rotate(b1_curr, rot);  
                    vector<int> d{b_i[0] - b1_curr[0], b_i[1] - b1_curr[1], b_i[2] - b1_curr[2]}; 
                    translate(b1_curr, d);
                    updated_beacons[i1_curr] = b1_curr;
                    int counter = 1;    
                    for(unsigned int i2_curr = 0; i2_curr < scans[curr].size(); ++i2_curr) {
                        if(i1_curr == i2_curr) continue;
                        vector<int> b2_curr = scans[curr][i2_curr];
                        rotate(b2_curr, rot);
                        translate(b2_curr, d);
                        updated_beacons[i2_curr] = b2_curr;
                        if(has_beacon(i, b2_curr, scans)) {
                            ++counter;
                        }
                    }
                    if(counter >= 12) {
                        for(unsigned int i2_curr = 0; i2_curr < scans[curr].size(); ++i2_curr) {
                            scans[curr][i2_curr] = updated_beacons[i2_curr];
                        }
                        translate(scanner_positions[curr],d);
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

int main(int argc, char const *argv[]) {
    vector<vector<vector<int>>> scans;
    vector<vector<int>> scanner_positions;
    string coord_str, scanner_id_str;
    queue<int> remaining;
    int counter = 0;
    while(getline(cin,scanner_id_str)) {
        vector<vector<int>> current_scan;
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
        scanner_positions.push_back({0,0,0});
        remaining.push(counter++);
    }
    vector<vector<int>> tested(scans.size(), vector<int>(scans.size(),0));
    vector<int> fitted = {0};
    remaining.pop();
    --counter;
    while(counter) {
        const int curr = remaining.front();
        remaining.pop();
        if(new_fit(curr, fitted, scans, tested, scanner_positions)) {
            fitted.push_back(curr);
            --counter;
        } else {
            remaining.push(curr);
        }
        cout << "Remaining scanners to fit: " << counter << endl;
    }

    int max = 0;
    for(unsigned int i = 0; i < scans.size(); ++i) {
        //cout << "Scanner " << i << ":\t" << scanner_positions[i][0] << ',' << scanner_positions[i][1] << ',' << scanner_positions[i][2] << endl;
        for(unsigned int j = i + 1; j < scans.size(); ++j) {
            int man_dist =  abs(scanner_positions[i][0] - scanner_positions[j][0]) + 
                            abs(scanner_positions[i][1] - scanner_positions[j][1]) + 
                            abs(scanner_positions[i][2] - scanner_positions[j][2]);
            if(man_dist > max) max = man_dist;
        }
    }
    cout << "Answer: " << max << endl;
    return 0;
}
