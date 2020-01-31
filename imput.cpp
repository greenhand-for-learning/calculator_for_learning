#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

void io_sto(char key, double value);
double call_sto(char key);

double transd(string word)
{
    return atof(word.c_str());
}

char transc(string word)
{
    return word[0];
}

void imput(string line)
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