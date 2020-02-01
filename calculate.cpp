//
// Created by Bruce on 2020/1/31.
//

#include <cmath>
#include <string>
#include <sstream>
#include <iostream>
using namespace std;

double calculate_with_real(string & formula, bool & valid, string DorR = "R", int start = 0, int finish = 0x7fffffff){
    if(finish > formula.length()){
        finish = formula.length();
    }
    double const PI = 3.14159265;
    double block[1000] = {0};
    int sign[1000] = {0};
    bool isblock[1000] = {false};
    int tail = 1;
    int g = 0;
    string tmp;
    stringstream * ss;
    int lev = 0;
    int now_lev;

    for(int i = start; i < finish; i ++){
        if(!valid){
            return -1;
        }

        if(formula[i] == ' '){
            continue;
        }

        if((formula[i] >= '0' && formula[i] <= '9') || formula[i] == '.') {
            g = 0;
            while ((formula[i] >= '0' && formula[i] <= '9') || formula[i] == '.') {
                //cout << formula[i] << endl;
                if (formula[i] == '.') {
                    if (++g >= 2) {
                        cout << "Invalid input! Please check your use of period." << endl;
                        valid = false;
                        return -1;
                    }
                }
                tmp += formula[i];
                i++;
                if(i >= finish){ break;}
            }
            ss = new stringstream;
            //cout << "tmp: " << tmp << endl;
            *ss << tmp;
            *ss >> block[tail];
            //cout << "number:" << block[tail] << endl;
            delete ss;
            isblock[tail] = true;
            tail ++;
            tmp = "";
            g = 0;
            i--;
            continue;
        }

        if(formula[i] == '('){
            g = 1;
            i++;
            int now = i;
            while(g){
                if(i >= finish){
                    cout << "Invalid input! Please check your use of parentheses." << endl;
                    valid = false;
                    return -1;
                }
                if(formula[i] == '('){
                    g++;
                }
                else if(formula[i] == ')'){
                    g--;
                }
                i++;
            }
            i--;
            block[tail] = calculate_with_real(formula, valid, DorR, now, i);
            isblock[tail] = true;
            tail ++;
            continue;
        }

        if(formula[i] == ')'){
            cout << "Invalid input! Please check your use of parentheses." << endl;
            valid = false;
            return -1;
        }

        if(formula[i] == '+' || formula[i] == '-' || formula[i] == '*' || formula[i] == '/'){
            if(formula[i] == '+' || formula[i] == '-'){now_lev = 1;}
            else if(formula[i] == '*' || formula[i] == '/'){now_lev = 2;}

            if(lev >= now_lev){
                if(tail < 4 || !isblock[tail - 1] || !isblock[tail - 3] || isblock[tail - 2] || isblock[tail - 4]){
                    cout << "Invalid input! Please check your formula." << endl;
                    valid = false;
                    return -1;
                }
                while(lev >= now_lev) {
                    if (sign[tail - 2] == 1) { block[tail - 3] += block[tail - 1]; }
                    else if (sign[tail - 2] == 2) { block[tail - 3] -= block[tail - 1]; }
                    else if (sign[tail - 2] == 3) { block[tail - 3] *= block[tail - 1]; }
                    else if (sign[tail - 2] == 4) { block[tail - 3] /= block[tail - 1]; }
                    if(sign[tail - 4] == 0) {lev = 0;}
                    if(sign[tail - 4] == 1 || sign[tail - 4] == 2) {lev = 1;}
                    if(sign[tail - 4] == 3 || sign[tail - 4] == 4) {lev = 2;}
                    tail -= 2;
                }
            }

            if(formula[i] == '+'){//No.1, Lv.1
                sign[tail] = 1;
                isblock[tail] = false;
                tail ++;
            }
            else if(formula[i] == '-'){//No.2, Lv.1
                sign[tail] = 2;
                isblock[tail] = false;
                tail ++;
            }
            else if(formula[i] == '*'){//No.3, Lv.2
                sign[tail] = 3;
                isblock[tail] = false;
                tail ++;
            }
            else if(formula[i] == '/'){//No.4, Lv.2
                sign[tail] = 4;
                isblock[tail] = false;
                tail ++;
            }
            lev = now_lev;
        }
    }
    /*
    for(int i = 0; i < tail + 4; i ++){
        cout << block[i] << ' ';
    }
    cout << endl;
    for(int i = 0; i < tail + 4; i ++){
        cout << sign[i] << ' ';
    }
    cout << endl;
    for(int i = 0; i < tail + 4; i ++){
        cout << isblock[i] << ' ';
    }
    cout << endl;
     */
    ///These codes are entirely the same as those in loop.
    now_lev = 1;
    if(lev >= now_lev){
        if(tail < 4 || !isblock[tail - 1] || !isblock[tail - 3] || isblock[tail - 2] || isblock[tail - 4]){
            cout << "Invalid input! Please check your formula." << endl;
            valid = false;
            return -1;
        }
        while(lev >= now_lev) {
            if (sign[tail - 2] == 1) { block[tail - 3] += block[tail - 1]; }
            else if (sign[tail - 2] == 2) { block[tail - 3] -= block[tail - 1]; }
            else if (sign[tail - 2] == 3) { block[tail - 3] *= block[tail - 1]; }
            else if (sign[tail - 2] == 4) { block[tail - 3] /= block[tail - 1]; }
            if(sign[tail - 4] == 0) {lev = 0;}
            if(sign[tail - 4] == 1 || sign[tail - 4] == 2) {lev = 1;}
            if(sign[tail - 4] == 3 || sign[tail - 4] == 4) {lev = 2;}
            tail -= 2;
        }
    }
    if(tail == 4){
        if (sign[tail - 2] == 1) { block[tail - 3] += block[tail - 1]; }
        else if (sign[tail - 2] == 2) { block[tail - 3] -= block[tail - 1]; }
        else if (sign[tail - 2] == 3) { block[tail - 3] *= block[tail - 1]; }
        else if (sign[tail - 2] == 4) { block[tail - 3] /= block[tail - 1]; }
    }
    return block[1];
}