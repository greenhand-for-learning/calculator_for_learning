//
// Created by Bruce on 2020/1/31.
//

#ifndef CASIO_CALCULATE_H
#define CASIO_CALCULATE_H

#include <string>
using namespace std;

double calculate_with_real(string & formula, bool & valid, string DorR = "R", int start = 0, int finish = 0x7fffffff);

#endif //CASIO_CALCULATE_H
