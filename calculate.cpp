//
// Created by Bruce on 2020/1/31.
//

#include <cmath>
#include <string>
#include <sstream>
#include <iostream>
#include "storage.h"
#define INF_SMALL 1e-10
#define PI 3.141592653589793238462643383279
#define e_mathematics 2.718281828459045235360287471352
using namespace std;

double D2R(double D){
    return D * PI / 180;
}

double R2D(double R){
    return R * 180 / PI;
}

bool IsInteger(double num){
    double * intpart = new double;
    num = modf(num, intpart);
    delete intpart;
    return abs(num) < INF_SMALL;
}

double get_number(string & formula, int & i, bool & valid, int finish){
    int g = 0;
    string tmp;
    double ret;

    while ((formula[i] >= '0' && formula[i] <= '9') || formula[i] == '.') {
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
    stringstream ss;
    ss << tmp;
    ss >> ret;
    if(formula[i] != 'E') {
        i--;
    } else {
        bool sign;
        i++;
        if(formula[i] == '+'){
            sign = true;
        }
        else if(formula[i] == '-'){
            sign = false;
        }
        else{
            cout << "Invalid input! E must be followed by + or -." << endl;
            valid = false;
            return -1;
        }
        i++;
        double idx = get_number(formula, i, valid, finish);
        if(!IsInteger(idx)){
            cout << "Invalid input! E must be followed by + or -, and then an integer." << endl;
            valid = false;
            return -1;
        }
        if(sign){
            ret = ret * pow(10.0, idx);
        } else {
            ret = ret * pow(10.0, -idx);
        }
    }
    return ret;
}

string get_string(string & formula, int & i, bool & valid, int finish){
    string tmp;
    while((formula[i] >= 'a' && formula[i] <= 'z') && formula[i] != 'x' && formula[i] != 'y'){
        tmp += formula[i];
        i ++;
        if(i >= finish){ break;}
    }
    i--;
    return tmp;
}

void load_number(double * block, int * sign, bool * isblock, int & tail, int & lev, double num){
    if(isblock[tail - 1]){
        cout << "Warning: Consecutive 2 scalars will automatically add a * between them." << endl;
        sign[tail] = 3;
        isblock[tail] = false;
        tail++;
        lev = 2;
    }
    block[tail] = num;
    isblock[tail] = true;
    tail ++;
}

int get_parentheses(string & formula, int & i, bool & valid, int finish){
    int g = 1;
    i++;
    int ret = i;
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
    return ret;
}

void compute(double * block, int * sign, bool * isblock, int & tail, int & lev, int now_lev, bool & valid){
    if(lev >= now_lev){
        if(tail < 4 || !isblock[tail - 1] || !isblock[tail - 3] || isblock[tail - 2] || isblock[tail - 4]){
            cout << "Invalid input! Please check your formula." << endl;
            valid = false;
            return;
        }
        while(lev >= now_lev) {
            if (sign[tail - 2] == 1) { block[tail - 3] += block[tail - 1]; }
            else if (sign[tail - 2] == 2) { block[tail - 3] -= block[tail - 1]; }
            else if (sign[tail - 2] == 3) { block[tail - 3] *= block[tail - 1]; }
            else if (sign[tail - 2] == 4) {
                if(abs(block[tail - 1]) < INF_SMALL){
                    cout << "Mathematical error! 0 should not be put after /." << endl;
                    valid = false;
                    return;
                }
                block[tail - 3] /= block[tail - 1];
            }
            if(sign[tail - 4] == 0) {lev = 0;}
            if(sign[tail - 4] == 1 || sign[tail - 4] == 2) {lev = 1;}
            if(sign[tail - 4] == 3 || sign[tail - 4] == 4) {lev = 2;}
            tail -= 2;
        }
    }
}

double calculate_with_real(string & formula, bool & valid, string DorR = "R", int start = 0, int finish = 0x7fffffff){
    if(finish > formula.length()){
        finish = formula.length();
    }
    double block[1000] = {0};
    int sign[1000] = {0};
    bool isblock[1000] = {false};
    int tail = 1;
    int lev = 0;

    for(int i = start; i < finish; i ++){
        if(!valid){
            return -1;
        }

        if(formula[i] == ' '){
            continue;
        }

        if((formula[i] >= '0' && formula[i] <= '9') || formula[i] == '.') {
            double tmp2 = get_number(formula, i, valid, finish);
            load_number(block, sign, isblock, tail, lev, tmp2);
            continue;
        }

        if(formula[i] == '('){
            int now = get_parentheses(formula, i, valid, finish);
            double tmp2 = calculate_with_real(formula, valid, DorR, now, i);
            load_number(block, sign, isblock, tail, lev, tmp2);
            continue;
        }

        if(formula[i] == ')'){
            cout << "Invalid input! Please check your use of parentheses." << endl;
            valid = false;
            return -1;
        }

        if(formula[i] == '+' || formula[i] == '-' || formula[i] == '*' || formula[i] == '/'){
            int now_lev;
            if(formula[i] == '+' || formula[i] == '-'){now_lev = 1;}
            else if(formula[i] == '*' || formula[i] == '/'){now_lev = 2;}

            compute(block, sign, isblock, tail, lev, now_lev, valid);

            if(formula[i] == '+'){//No.1, Lv.1
                if(tail == 1){
                    block[tail] = 0;
                    isblock[tail] = true;
                    tail ++;
                }
                sign[tail] = 1;
                isblock[tail] = false;
                tail ++;
            }
            else if(formula[i] == '-'){//No.2, Lv.1
                if(tail == 1){
                    block[tail] = 0;
                    isblock[tail] = true;
                    tail ++;
                }
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
            continue;
        }

        if(formula[i] == '^'){
            i ++;
            while(i < finish && formula[i] == ' '){i++;}
            if(i >= finish){
                cout << "Invalid input! There is something wrong in the use of ^." << endl;
                valid = false;
                return -1;
            }
            if(formula[i] != '('){
                cout << "Invalid input! ^ must be followed by parentheses()." << endl;
                valid = false;
                return -1;
            }
            int now = get_parentheses(formula, i, valid, finish);
            double tmp2 = calculate_with_real(formula, valid, DorR, now, i);
            if(!isblock[tail - 1]){
                cout << "Invalid input! Please check your use of ^." << endl;
                valid = false;
                return -1;
            }
            if((abs(block[tail - 1]) < INF_SMALL && tmp2 < INF_SMALL)
                || (block[tail - 1] <= -INF_SMALL && !IsInteger(tmp2)))
            {
                cout << "Mathematical error! There is something wrong when you use ^." << endl;
                valid = false;
                return -1;
            }
            block[tail - 1] = pow(block[tail - 1], tmp2);
            continue;
        }

        if((formula[i] >= 'A' && formula[i] <= 'D') || formula[i] == 'x' || formula[i] == 'y' || formula[i] == 'M'){
            double tmp2 = call_sto(formula[i]);
            load_number(block, sign, isblock, tail, lev, tmp2);
            continue;
        }

        if((formula[i] >= 'a' && formula[i] <= 'z') && formula[i] != 'x' && formula[i] != 'y'){
            string tmp = get_string(formula, i, valid, finish);

            if(tmp == "sin" || tmp == "cos" || tmp == "tan" || tmp == "arcsin" || tmp == "arccos" || tmp == "arctan"
                            || tmp == "sinh" || tmp == "cosh" || tmp == "tanh"
                            || tmp == "exp" || tmp == "ln" || tmp == "lg" || tmp == "sqrt" || tmp == "cbrt"){
                //These codes are entirely the same as those if formula[i] == '^'.
                i++;
                while(i < finish && formula[i] == ' '){i++;}
                if(i >= finish){
                    cout << "Invalid input! There is something wrong in the use of such function." << endl;
                    valid = false;
                    return -1;
                }
                if(formula[i] != '('){
                    cout << "Invalid input! Such function must be followed by parentheses()." << endl;
                    valid = false;
                    return -1;
                }
                int now = get_parentheses(formula, i, valid, finish);
                double tmp2 = calculate_with_real(formula, valid, DorR, now, i);

                if(tmp == "sin" || tmp == "cos" || tmp == "tan"){
                    if(DorR == "D"){
                        tmp2 = D2R(tmp2);
                    }
                    if(tmp == "sin"){tmp2 = sin(tmp2);}
                    else if(tmp == "cos"){tmp2 = cos(tmp2);}
                    else if(tmp == "tan"){
                        if(IsInteger((tmp2 - PI / 2) / PI)){
                            cout << "Mathematical error! There is something wrong when you use tan." << endl;
                            valid = false;
                            return -1;
                        }
                        tmp2 = tan(tmp2);
                    }
                }
                else if(tmp == "arcsin" || tmp == "arccos" || tmp == "arctan"){
                    if(tmp == "arcsin"){
                        if(tmp2 > 1 || tmp2 < -1){
                            cout << "Mathematical error! There is something wrong when you use arcsin." << endl;
                            valid = false;
                            return -1;
                        }
                        tmp2 = asin(tmp2);
                    }
                    else if(tmp == "arccos"){
                        if(tmp2 > 1 || tmp2 < -1){
                            cout << "Mathematical error! There is something wrong when you use arccos." << endl;
                            valid = false;
                            return -1;
                        }
                        tmp2 = acos(tmp2);
                    }
                    else if(tmp == "arctan"){tmp2 = atan(tmp2);}
                    if(DorR == "D"){
                        tmp2 = R2D(tmp2);
                    }
                }
                else if(tmp == "tanh" || tmp == "cosh" || tmp == "sinh"
                        ||tmp == "exp" || tmp == "ln" || tmp == "lg" || tmp == "sqrt" || tmp == "cbrt"){
                    if(tmp == "sinh"){tmp2 = sinh(tmp2);}
                    else if(tmp == "cosh"){tmp2 = cosh(tmp2);}
                    else if(tmp == "tanh"){tmp2 = tanh(tmp2);}
                    else if(tmp == "exp"){tmp2 = exp(tmp2);}
                    else if(tmp == "ln"){
                        if(tmp2 < INF_SMALL){
                            cout << "Mathematical error! There is something wrong when you use ln." << endl;
                            valid = false;
                            return -1;
                        }
                        tmp2 = log(tmp2);
                    }
                    else if(tmp == "lg"){
                        if(tmp2 < INF_SMALL){
                            cout << "Mathematical error! There is something wrong when you use lg." << endl;
                            valid = false;
                            return -1;
                        }
                        tmp2 = log10(tmp2);
                    }
                    else if(tmp == "sqrt"){
                        if(tmp2 < -INF_SMALL){
                            cout << "Mathematical error! There is something wrong when you use sqrt." << endl;
                            valid = false;
                            return -1;
                        }
                        else if(abs(tmp2) <= INF_SMALL){
                            tmp2 = 0;
                        }
                        else {
                            tmp2 = sqrt(tmp2);
                        }
                    }
                    else if(tmp == "cbrt"){tmp2 = cbrt(tmp2);}
                }
                load_number(block, sign, isblock, tail, lev, tmp2);
            }
            else if(tmp == "pi" || tmp == "e"){
                if(tmp == "pi"){
                    load_number(block, sign, isblock, tail, lev, PI);
                }
                else if(tmp == "e"){
                    load_number(block, sign, isblock, tail, lev, e_mathematics);
                }
            }
            else {
                cout << "Invalid input! Please check your use of function." << endl;
                valid = false;
                return -1;
            }

            continue;
        }
        cout << "Invalid input! Please check your formula." << endl;
        valid = false;
        return -1;
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
    int now_lev = 1;
    compute(block, sign, isblock, tail, lev, now_lev, valid);
    if(tail == 4){
        if (sign[tail - 2] == 1) { block[tail - 3] += block[tail - 1]; }
        else if (sign[tail - 2] == 2) { block[tail - 3] -= block[tail - 1]; }
        else if (sign[tail - 2] == 3) { block[tail - 3] *= block[tail - 1]; }
        else if (sign[tail - 2] == 4) { block[tail - 3] /= block[tail - 1]; }
    }
    if(abs(block[1]) < INF_SMALL){block[1] = 0;}
    return block[1];
}