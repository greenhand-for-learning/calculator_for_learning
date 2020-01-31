//
// Created by Bruce on 2020/1/31.
//

#include "complex.h"
#include <iostream>
#include <cstdio>
using namespace std;

double const complex::MIN = 0.001;

complex complex::operator+ (complex b){
    complex sum;
    sum.r = r + b.r;
    sum.c = c + b.c;
    return sum;
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