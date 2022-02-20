#include<iostream>
#include<algorithm>
#include<vector>
#include<limits>
#include<chrono>

using namespace std;

typedef long long bignum;

class Cube {
    public:
    const bignum x_min, x_max, y_min, y_max, z_min, z_max;
    const bignum size;
    const int on;
    Cube(   bignum xmin, bignum xmax, 
            bignum ymin, bignum ymax,
            bignum zmin, bignum zmax, 
            int on_in) : 
                x_min(xmin), x_max(xmax), 
                y_min(ymin), y_max(ymax), 
                z_min(zmin), z_max(zmax), 
                size((x_max - x_min + 1) * (y_max - y_min + 1) * (z_max - z_min + 1)),
                on(on_in) {}
};

bignum overlap(const Cube& c1, const Cube& c2) {
    const bignum dx = min<bignum>(c1.x_max, c2.x_max) - max<bignum>(c1.x_min, c2.x_min);
    const bignum dy = min<bignum>(c1.y_max, c2.y_max) - max<bignum>(c1.y_min, c2.y_min);
    const bignum dz = min<bignum>(c1.z_max, c2.z_max) - max<bignum>(c1.z_min, c2.z_min);
    return (dx >= 0 && dy >= 0 && dz >= 0);
}

Cube get_intersection(const Cube& c1, const Cube& c2) { 
    const bignum rx = min<bignum>(c1.x_max, c2.x_max), lx = max<bignum>(c1.x_min, c2.x_min);
    const bignum ry = min<bignum>(c1.y_max, c2.y_max), ly = max<bignum>(c1.y_min, c2.y_min);
    const bignum rz = min<bignum>(c1.z_max, c2.z_max), lz = max<bignum>(c1.z_min, c2.z_min);
    return Cube(lx, rx, ly, ry, lz, rz, -c2.on);
}

int main(int argc, char const *argv[]) {
    string line;
    bignum xlim[] = {0,0}, ylim[] = {0,0}, zlim[] = {0,0};
    vector<Cube> cuboids;
    while(getline(cin,line) && !line.empty()) {
        if(line.empty()) continue;
        const int on = line[1] == 'n' ? 1 : 0;
        size_t shift = on ? 5 : 6;
        const size_t first_dot = line.find('.');
        const size_t first_comma = line.find(',');
        const size_t second_dot = line.find('.',first_comma);
        const size_t second_comma = line.find(',',second_dot);
        const size_t third_dot = line.find('.',second_comma);
        xlim[0] = stoi(line.substr(shift, first_dot - shift));
        shift = first_dot + 2;
        xlim[1] = stoi(line.substr(shift, first_comma - shift));
        shift = first_comma + 3;
        ylim[0] = stoi(line.substr(shift, second_dot - shift));
        shift = second_dot + 2;
        ylim[1] = stoi(line.substr(shift, second_comma - shift));
        shift = second_comma + 3;
        zlim[0] = stoi(line.substr(shift, third_dot - shift));
        shift = third_dot + 2;
        zlim[1] = stoi(line.substr(shift));
        cuboids.push_back({ xlim[0], xlim[1],
                            ylim[0], ylim[1],
                            zlim[0], zlim[1],
                            on  });
    }
    vector<Cube> cores, new_cores;
    for(const Cube& cuboid : cuboids) {
        new_cores.clear();
        if( cuboid.on ) new_cores.push_back(cuboid);
        for(const Cube& c_core : cores) {
            if(overlap(cuboid, c_core)) {
                new_cores.push_back(get_intersection(cuboid, c_core));
            }
        }
        for(const Cube& new_c : new_cores) {
            cores.push_back(new_c);
        }
    }
    bignum result = 0;
    for(const Cube& c : cores) {        
        result += c.on * c.size;
    }
    cout << result << endl;
    return 0;
}
