//
// Created by huangb19 on 2020/2/2.
//

#include <cmath>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;
typedef long long ll;

bool errflag;
ll base2oct(int base, string num){
    ll ret = 0;
    int l = num.length();
    for(int i = l - 1; i >= 0; i--){
        int k = 0;
        if(num[i] >= '0' && num[i] <= '9') k =  num[i] - '0';
        else if(num[i] == 'A') k = 10;
        else if(num[i] == 'B') k = 11;
        else if(num[i] == 'C') k = 12;
        else if(num[i] == 'D') k = 13;
        else if(num[i] == 'E') k = 14;
        else if(num[i] == 'F') k = 15;
        else errflag = 1;

        if(k >= base)errflag = 1;
        ret = ret * base + k;
    }
    return ret;
}

string oct2base(int base, ll num){
    string ret = "";
    int nnum = abs(num);
    while(nnum){
        int k = nnum % base;
        if(k <= 9)ret += ("0" + k);
        else if(k == 10)ret += "A";
        else if(k == 11)ret += "B";
        else if(k == 12)ret += "C";
        else if(k == 13)ret += "D";
        else if(k == 14)ret += "E";
        else if(k == 15)ret += "F";
        nnum /= base;
    }
    reverse(ret.begin(), ret.end());
    if(num == 0) ret = "0";
    else if(num < 0) ret = "-" + ret;
    return ret;
}

void init(){

}


void radix_main(){
    errflag = 0;
    int base;
    string s;
    cout << "radix mode" << endl;
    cout << "input the base (2 <= base <= 16) :" << endl;
    cin >> base;
    cout << "input the expression :" << endl;
    getchar();
    getline(cin, s);




    return;
}
