#include<iostream>
#include<queue>

using namespace std;

int bin_repr(const char& c) {
    if(c == '0') {
        return 0x0;
    } else if(c == '1') {
        return 0x1;
    } else if(c == '2') {
        return 0x2;
    } else if(c == '3') {
        return 0x3;
    } else if(c == '4') {
        return 0x4;
    } else if(c == '5') {
        return 0x5;
    } else if(c == '6') {
        return 0x6;
    } else if(c == '7') {
        return 0x7;
    } else if(c == '8') {
        return 0x8;
    } else if(c == '9') {
        return 0x9;
    } else if(c == 'A') {
        return 0xA;
    } else if(c == 'B') {
        return 0xB;
    } else if(c == 'C') {
        return 0xC;
    } else if(c == 'D') {
        return 0xD;
    } else if(c == 'E') {
        return 0xE;
    } else if(c == 'F') {
        return 0xF;
    } 
    return 0;
}

int get_bit_at(const string& transmission, const int bit_pos) {
    const unsigned int byte_pos = bit_pos / 4;
    if(byte_pos >= transmission.length()) return 0;
    return (bin_repr(transmission[byte_pos]) & (0x8 >> (bit_pos % 4))) >> (3 - (bit_pos % 4));
}   

// Tokens
// type id = 4 -> number
// type id != 4 -> operator
//      bit 7 (after header) = 1 -> next 15 bits are a number that represents total bits of sub-packets
//      -||- = 0 -> next 11 bits are a number that represent number of sub-packets in packet

// tokens are stored : type_id1 , num1, type_id2, num2, .... , type_idn, numn

void tokenize(queue<pair<int,int>>& token_q, const string& transmission_str) {
    int pos = 0;
    const int end = transmission_str.length() * 4;
    while(pos < end) {
        int number = 0;
        const int vers = (get_bit_at(transmission_str, pos) << 2) | (get_bit_at(transmission_str, pos+1) << 1) | get_bit_at(transmission_str, pos+2);
        const int type_id = (get_bit_at(transmission_str, pos+3) << 2) | (get_bit_at(transmission_str, pos+4) << 1) | get_bit_at(transmission_str, pos+5);        
        pos += 6;
        if(type_id == 4) {  // number literal
            int byte;
            while(get_bit_at(transmission_str, pos)) {
                byte = (get_bit_at(transmission_str, pos+1) << 3) | (get_bit_at(transmission_str, pos+2) << 2) | (get_bit_at(transmission_str, pos+3) << 1) | get_bit_at(transmission_str,pos+4);
                number <<= 4;
                number |= byte;
                pos += 5;
            } 
            byte = (get_bit_at(transmission_str, pos+1) << 3) | (get_bit_at(transmission_str, pos+2) << 2) | (get_bit_at(transmission_str, pos+3) << 1) | get_bit_at(transmission_str,pos+4);
            number <<= 4;
            number |= byte;
            pos += 5;
        } else {    // operator
            int num_bits = get_bit_at(transmission_str, pos) ? 11 : 15;
            for(int i = 0; i < num_bits; ++i) {
                number <<= 1;
                number |= get_bit_at(transmission_str,++pos);
            }
            ++pos;
        }
        token_q.push({vers,number});
    }
}

int main(int argc, char const *argv[])
{
    string transmission_str;
    cin >> transmission_str;
    queue<pair<int,int>> token_q;
    tokenize(token_q, transmission_str);
    int vers_sum = 0;
    while(!token_q.empty()) {
        vers_sum += token_q.front().first;
        token_q.pop();
    }
    cout << vers_sum << endl;
    return 0;
}


