#include<iostream>
#include<vector>

#define NUM_STEPS 50

using namespace std;

typedef vector<vector<int>> image;

ostream& operator<<(ostream& out, const image& img) {
    for(unsigned int i = 0; i < img.size(); ++i) {
        for(unsigned int j = 0; j < img[0].size(); ++j) {
            out << (img[i][j] ? '#' : '.');
        }
        out << endl;
    }
    return out;
}

int main(int argc, char const *argv[]) {
    string algo_str, line;
    vector<vector<int>> input_img;
    bool first = false, last = false;
    getline(cin, algo_str);
    if(algo_str[0] == '#') first = true;
    if(algo_str[algo_str.size()-1] == '#') last = true;
    getline(cin, line);
    while(getline(cin, line)) {
        vector<int> img_row(line.size(), 0);
        for(unsigned int i = 0; i < line.size(); ++i) {
            if(line[i] == '#') img_row[i] = 1;
        }
        input_img.push_back(img_row);
    }
    image img(input_img.size() + 2*NUM_STEPS, vector<int>(input_img[0].size() + 2*NUM_STEPS, 0));
    image tmp_img(input_img.size() + 2*NUM_STEPS, vector<int>(input_img[0].size() + 2*NUM_STEPS, 0));
    for(unsigned int i = 0; i < input_img.size(); ++i) {
        for(unsigned int j = 0; j < input_img[0].size(); ++j) {
            img[NUM_STEPS+i][NUM_STEPS+j] = input_img[i][j];
        }   
    }
    for(int step = NUM_STEPS; step > 0; --step) {
        for(int i = 0; i < img.size(); ++i) {
            for(int j = 0; j < img[0].size(); ++j) {
                int num = 0;
                for(int ii = -1; ii < 2; ++ii) {
                    for(int jj = -1; jj < 2; ++jj) {
                        num <<= 1;
                        if( (i + ii < 0 || i + ii >= img.size()) ||
                            (j + jj < 0 || j + jj >= img[0].size()) ) {
                                if(!first) continue;
                                if(last || (NUM_STEPS - step) % 2) {
                                    num |= 0x1;
                                } 
                        } else if(img[i+ii][j+jj]) num |= 0x1;
                    }
                }
                if(num >= algo_str.size()) {
                    cout << "ERROR! algo index too large: " << num << endl;
                    return 0;
                }
                tmp_img[i][j] = (algo_str[num] == '#' ? 1 : 0);
            }
        }
        img.swap(tmp_img);
    }
    int counter = 0;
    for(unsigned int i = 0; i < img.size(); ++i) {
        for(unsigned int j = 0; j < img[0].size(); ++j) {
            if(img[i][j]) ++counter;
        }
    }
    cout << img << endl;
    cout << "Answer: " << counter << endl;
    return 0;
}
