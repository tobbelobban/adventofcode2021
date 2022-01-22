#include<iostream>
#include<vector>
#include<cmath>
#include<queue>
#include<unordered_map>

using namespace std;

typedef vector<vector<double>> matrix;

double beacon_distance(const vector<double>& b1, const vector<double>& b2) {
    return  sqrt(   (b1[0] - b2[0])*(b1[0] - b2[0]) + 
                    (b1[1] - b2[1])*(b1[1] - b2[1]) + 
                    (b1[2] - b2[2])*(b1[2] - b2[2]) ); 
}

int main(int argc, char const *argv[]) {
    vector<vector<vector<double>>> beacon_scans;
    string coord_str, scanner_id_str;
    // read input
    while(getline(cin,scanner_id_str)) {
        vector<vector<double>> current_scanner;
        while(getline(cin, coord_str) && !coord_str.empty()) {
            vector<double> coords;
            int first_comma_pos = coord_str.find(',');
            coords.push_back(stod(coord_str.substr(0,first_comma_pos)));

            int second_comma_pos = coord_str.find(',', first_comma_pos+1);
            coords.push_back(stod(coord_str.substr(first_comma_pos+1, second_comma_pos-first_comma_pos)));
            
            coords.push_back(stod(coord_str.substr(second_comma_pos+1)));
            current_scanner.push_back(coords);
        }
        beacon_scans.push_back(current_scanner);
    }
    vector<matrix> d_matrices;
    // create distance matrices
    const int num_scanners = beacon_scans.size();
    for(int s = 0; s < num_scanners; ++s) {
        const int num_beacons = beacon_scans[s].size();
        matrix d_matrix(num_beacons,vector<double>(num_beacons,0));
        for(int b1 = 0; b1 < num_beacons; ++b1) {
            for(int b2 = b1+1; b2 < num_beacons; ++b2) {
                const double distance = beacon_distance(beacon_scans[s][b1], beacon_scans[s][b2]);
                d_matrix[b1][b2] = distance;
                d_matrix[b2][b1] = distance;
            }
        }
        d_matrices.push_back(d_matrix);
    }
    
    return 0;
}
