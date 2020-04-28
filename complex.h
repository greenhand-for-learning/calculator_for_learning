//
// Created by Bruce on 2020/1/31.
//

#ifndef CASIO_COMPLEX_H
#define CASIO_COMPLEX_H

#include <iostream>
#include <string>
using namespace std;

class complex{
    static const double MIN;
    double r;
    double c;

public:
    complex(): r(), c(){};
    complex(double a, double b): r(a), c(b){};

    void show();

private:
    complex operator+ (complex b);
    complex operator- (complex b);
    complex operator* (complex b);
    complex operator/ (complex b);
    static complex power(complex a, int b);
};

complex calculate_with_complex(string formula);

#endif //CASIO_COMPLEX_H
