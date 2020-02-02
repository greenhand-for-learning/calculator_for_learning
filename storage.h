//
// Created by Bruce on 2020/2/2.
//

#ifndef CASIO_STORAGE_H
#define CASIO_STORAGE_H

#include <string>
using namespace std;

double transd(string word);
char transc(string word);
void input(string line);
void io_sto(char key, double value);
double call_sto(char key);
int variable2idx(char key);
void get_all(double * array);
void write_all(double * array);
void write_all_with_one_num(double num);

#endif //CASIO_STORAGE_H
