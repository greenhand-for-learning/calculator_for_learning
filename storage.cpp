#include <fstream>
#include <iostream>
#include <string>
using namespace std;

void io_sto(char key, double value)
{
    ifstream i_storage("storage.txt");
    double sto_num[10];
    for (int i = 0; i < 9; i++) {
        i_storage >> sto_num[i];
    }
    if (key >= 65 && key <= 70) {
        sto_num[(int)(key - 'A')] = value;
    } else if (key == 'x') {
        sto_num[6] = value;
    } else if (key == 'y') {
        sto_num[7] = value;
    } else {
        sto_num[8] = value;
    }
    ofstream o_storage("storage.txt");
    for (int i = 0; i < 9; i++) {
        o_storage << sto_num[i] << endl;
    }
    return;
}

double call_sto(char key)
{
    ifstream c_storage("storage.txt");
    double sto_num[10];
    for (int i = 0; i < 9; i++) {
        c_storage >> sto_num[i];
    }
    if (key >= 65 && key <= 70) {
        return sto_num[(int)(key - 'A')];
    } else if (key == 'x') {
        return sto_num[6];
    } else if (key == 'y') {
        return sto_num[7];
    } else {
        return sto_num[8];
    }
}