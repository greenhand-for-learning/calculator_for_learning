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

int variable2idx(char key){
    if(key >= 'A' && key <= 'D'){///A: 0, B: 1, C: 2, D: 3, x: 6, y: 7, M: 8
        return key - 'A';
    }
    else if(key == 'x'){
        return 6;
    }
    else if(key == 'y'){
        return 7;
    }
    else if(key == 'M'){
        return 8;
    }
    else {
        return -1;
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
    sto_num[variable2idx(key)] = value;
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
    c_storage.close();
    return sto_num[variable2idx(key)];
}

void get_all(double * array){
    ifstream i_storage("storage.txt");
    //ifstream i_storage("/Users/pc/Documents/undergraduate/Freshman spring/vacation/CASIO/storage.txt");
    for(int i = 0; i < 9; i ++){
        i_storage >> array[i];
    }
    i_storage.close();
}

void write_all(double * array){
    ofstream o_storage("storage.txt");
    //ofstream o_storage("/Users/pc/Documents/undergraduate/Freshman spring/vacation/CASIO/storage.txt");
    for(int i = 0; i < 9; i ++){
        o_storage << array[i] << endl;
    }
    o_storage.close();
}

void write_all_with_one_num(double num){
    ofstream o_storage("storage.txt");
    //ofstream o_storage("/Users/pc/Documents/undergraduate/Freshman spring/vacation/CASIO/storage.txt");
    for(int i = 0; i < 9; i ++){
        o_storage << num << endl;
    }
    o_storage.close();
}