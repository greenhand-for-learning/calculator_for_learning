//
// Created by Bruce on 2020/1/31.
//

#ifndef CASIO_COMPLEX_H
#define CASIO_COMPLEX_H

#include <iostream>
using namespace std;

class complex{
    static const double MIN;
    double r;
    double c;

public:
    complex(): r(), c(){};
    complex(double a, double b): r(a), c(b){
        cout << "Welcome to complex mode!" << endl;
    }

    void show();

private:
    complex operator+ (complex b);
};

#endif //CASIO_COMPLEX_H
