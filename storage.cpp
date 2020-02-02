#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include "storage.h"
using namespace std;

double transd(string word)
{
    return atof(word.c_str());
}

char transc(string word)
{
    return word[0];
}

void input(string line)
{
    string word[100];
    int l = line.length();
    for (int i = 0; i < 10; i++) {
        word[i].erase(0);
    }
    int j = 0;
    for (int i = 0; i < l; i++) {
        while (line[i] != ' ' && i < l) {
            word[j] += line[i];
            i++;
        }
        j++;
    }
    /*for (int i = 0; i < j; i++) {
        cout << word[i] << " ";
    }
    cout << endl;*/
    if (word[0] == "STO" && word[1] != "CALL") {
        io_sto(transc(word[1]),transd(word[2]));
    }
    else if(word[0]=="STO"&&word[1]=="CALL"){
        call_sto(transc(word[2]));
    }
}

void io_sto(char key, double value)
{
    ifstream i_storage("storage.txt");
    //ifstream i_storage("/Users/pc/Documents/undergraduate/Freshman spring/vacation/CASIO/storage.txt");
    double sto_num[10];
    for (int i = 0; i < 9; i++) {
        i_storage >> sto_num[i];
    }
    if (key >= 'A' && key <= 'D') {///A: 0, B: 1, C: 2, D: 3, x: 6, y: 7, M: 8
        sto_num[(int)(key - 'A')] = value;
    } else if (key == 'x') {
        sto_num[6] = value;
    } else if (key == 'y') {
        sto_num[7] = value;
    } else if (key == 'M'){
        sto_num[8] = value;
    }
    ofstream o_storage("storage.txt");
    //ofstream o_storage("/Users/pc/Documents/undergraduate/Freshman spring/vacation/CASIO/storage.txt");
    for (int i = 0; i < 9; i++) {
        o_storage << sto_num[i] << endl;
    }
    i_storage.close();
    o_storage.close();
}

double call_sto(char key)
{
    ifstream c_storage("storage.txt");
    //ifstream c_storage("/Users/pc/Documents/undergraduate/Freshman spring/vacation/CASIO/storage.txt");
    double sto_num[10];
    for (int i = 0; i < 9; i++) {
        c_storage >> sto_num[i];
    }
    if (key >= 'A' && key <= 'D') {
        return sto_num[(int)(key - 'A')];
    } else if (key == 'x') {
        return sto_num[6];
    } else if (key == 'y') {
        return sto_num[7];
    } else if (key == 'M'){
        return sto_num[8];
    }
    c_storage.close();
}