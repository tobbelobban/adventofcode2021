#include<iostream>
#include<queue>
#include<limits>
#include<algorithm>

using namespace std;

typedef long long int bignum;
typedef pair<int,pair<bignum,bignum>> token;

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

bignum tokenize(queue<token>& token_q, const string& transmission_str) {
    // token -> { type_id, {number, # bits} }
    bignum pos = 0, sum_vers = 0;
    const bignum end = transmission_str.length() * 4;
    while(pos < end) {
        bignum number = 0, packet_start = pos;
        //if(pos + 6 >= end) break;
        const int vers = (get_bit_at(transmission_str, pos) << 2) | (get_bit_at(transmission_str, pos+1) << 1) | get_bit_at(transmission_str, pos+2);
        int type_id = (get_bit_at(transmission_str, pos+3) << 2) | (get_bit_at(transmission_str, pos+4) << 1) | get_bit_at(transmission_str, pos+5);        
        pos += 6; 
        sum_vers += vers;
        if(type_id == 4) {  // number literal
            bignum hex;
            while(get_bit_at(transmission_str, pos)) {
                hex = (get_bit_at(transmission_str, pos+1) << 3) | (get_bit_at(transmission_str, pos+2) << 2) | (get_bit_at(transmission_str, pos+3) << 1) | get_bit_at(transmission_str,pos+4);
                number <<= 4;
                number |= hex;
                pos += 5;
            } 
            //if(pos + 4 >= end) break;
            hex = (get_bit_at(transmission_str, pos+1) << 3) | (get_bit_at(transmission_str, pos+2) << 2) | (get_bit_at(transmission_str, pos+3) << 1) | get_bit_at(transmission_str,pos+4);
            number <<= 4;
            number |= hex;
            pos += 5;
        } else {    // operator
            const int len_type_id = get_bit_at(transmission_str, pos);
            type_id |= (len_type_id << 3);
            int num_bits = len_type_id ? 11 : 15;
            //if(pos + num_bits >= end) break;
            for(int i = 0; i < num_bits; ++i) {
                number <<= 1;
                number |= get_bit_at(transmission_str,++pos);
            }
            ++pos;
        }
        token_q.push({type_id,{number,pos-packet_start}});
    }
    return pos;
}

bignum evaluate(queue<token>& token_q, bignum& remaining_bits) {
    const token& p = token_q.front();
    int type_id = p.first & 0x7, len_type_id = (p.first & 0x8) >> 3;
    bignum number = p.second.first, packet_size = p.second.second;
    token_q.pop();
    //cout << remaining_bits << "\t" << type_id << "\t" << packet_size << "\t" << number << endl;
    bignum res, iter = number;
    if(type_id == 4) {
        res = number;
    } else if(type_id == 0) {
        res = 0;
        if(len_type_id) {
            while(iter--) res += evaluate(token_q, remaining_bits);
        } else {
            while(iter) res += evaluate(token_q, iter);
        }
    } else if(type_id == 1) {
        res = 1;
        if(len_type_id) {
            while(iter--) res *= evaluate(token_q, remaining_bits);
        } else {
            while(iter) res *= evaluate(token_q, iter);
        }
    } else if(type_id == 2) {
        res = numeric_limits<bignum>::max();
        if(len_type_id) {
            while(iter--) res = min({res,evaluate(token_q, remaining_bits)});
        } else {
            while(iter) res = min({res,evaluate(token_q, iter)});
        }
    } else if(type_id == 3) {
        res = numeric_limits<bignum>::min();
        if(len_type_id) {
            while(iter--) res = max({res,evaluate(token_q, remaining_bits)});
        } else {
            while(iter) res = max({res,evaluate(token_q, iter)});
        }
    } else if(type_id == 5) {
        if(len_type_id) {
            res = evaluate(token_q, remaining_bits) > evaluate(token_q, remaining_bits);
        } else {
            res = evaluate(token_q, iter) > evaluate(token_q, iter);
        }
    } else if(type_id == 6) {
        if(len_type_id) {
            res = evaluate(token_q, remaining_bits) < evaluate(token_q, remaining_bits);
        } else {
            res = evaluate(token_q, iter) < evaluate(token_q, iter);
        }
    } else if(type_id == 7) {
        if(len_type_id) {
            res = evaluate(token_q, remaining_bits) == evaluate(token_q, remaining_bits);
        } else {
            res = evaluate(token_q, iter) == evaluate(token_q, iter);
        }
    } 
    remaining_bits -= packet_size;
    if(type_id != 4 && !len_type_id) remaining_bits -= number;
    return res;
}

int main(int argc, char const *argv[])
{
    string transmission_str; 
    cin >> transmission_str;
    queue<token> token_q;
    bignum bits = tokenize(token_q, transmission_str);
    cout << evaluate(token_q, bits) << "  " << bits << endl;
    return 0;
}


