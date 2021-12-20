#include<iostream>
#include<limits>

using namespace std;

#define X_MIN 206
#define X_MAX 250

#define Y_MIN -105
#define Y_MAX -57

inline bool passed_box(const int& x, const int& y) {
    return x > X_MAX || y < Y_MIN;
}

inline bool not_inside_box(const int& x, const int& y) {
    return x < X_MIN || x > X_MAX || y < Y_MIN || y > Y_MAX;
}

int get_path_height(int x_vel, int y_vel) {
    int pos_x = 0, pos_y = 0, max_height = pos_y;
    while(not_inside_box(pos_x, pos_y)) {
        //cout << pos_x << "   " << pos_y << endl;
        pos_x += x_vel; pos_y += y_vel--;
        if(pos_y > max_height) max_height = pos_y;
        if(x_vel > 0) --x_vel;
        if(x_vel < 0) ++x_vel;
        if(passed_box(pos_x,pos_y)) return numeric_limits<int>::min();
    }
    return max_height;
}

int main(int argc, char const *argv[]) {
    // target area: x=206..250, y=-105..-57
    int count = 0;
    for(int x_vel = -300; x_vel < 300; ++x_vel) {
        for(int y_vel = -200; y_vel < 200; ++y_vel) {
            int res = get_path_height(x_vel,y_vel);
            if(res > numeric_limits<int>::min()) ++count;
        }
    }
    cout << count << endl;
    return 0;
}
