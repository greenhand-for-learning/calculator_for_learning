//
// Created by Bruce on 2020/1/31.
//

#include "complex.h"
#include <iostream>
#include <cstdio>
using namespace std;

double const complex::MIN = 0.001;

complex complex::operator+ (complex b){
    complex ret;
    ret.r = r + b.r;
    ret.c = c + b.c;
    return ret;
}

complex complex::operator- (complex b){
    complex ret;
    ret.r = r - b.r;
    ret.c = c - b.c;
    return ret;
}

complex complex::operator* (complex b){
    complex ret;
    ret.r = r * b.r - c * b.c;
    ret.c = r * b.c + c * b.r;
    return ret;
}

complex complex::operator/ (complex b){
    complex ret;
    ret.r = (r * b.r + c * b.c) / (b.r * b.r + b.c * b.c);
    ret.c = (c * b.r - r * b.c) / (b.r * b.r + b.c * b.c);
    return ret;
}

void complex::show() {
    bool real = r >= MIN || r <= -MIN, com = c >= MIN || c <= -MIN;
    if(real){
        cout << r;
        if(com){
            if(c > 0){
                cout << '+';
            }
            cout << c << 'i';
        }
    } else {
        cout << c << 'i';
    }
}