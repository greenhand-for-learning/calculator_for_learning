//
// Created by huangb19 on 2020/2/2.
//

#include <string>
#include <iostream>
#include <algorithm>
#include <stack>
using namespace std;
typedef long long ll;

bool errflag;
ll base2dec(int base, string num){
    ll ret = 0;
    int l = num.length();
    for(int i = 0; i < l; i++){
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

string dec2base(int base, ll num){
    string ret = "";
    int nnum = abs(num);
    while(nnum){
        int k = nnum % base;
        if(k <= 9)ret += ('0' + k);
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

stack <ll> s_num;
stack <char> s_op;
bool isnum(char s){
    return (s >= '0' && s <= '9') || (s >= 'A' && s <= 'F');
}
void cal_once(){
    if(s_num.size() <= 1 || s_op.top() == '(') {
        errflag = 1;
        cout << "Invalid expression" << endl;
        return;
    }
    ll n1 = s_num.top(); s_num.pop();
    ll n2 = s_num.top(); s_num.pop();
    char op = s_op.top(); s_op.pop();
    if(op == '+') s_num.push(n1 + n2);
    if(op == '-') s_num.push(n2 - n1);
    if(op == '*') s_num.push(n1 * n2);
    if(op == '/'){
        if(n2 != 0)s_num.push(n2 / n1);
        else{
            cout << "Division by 0" << endl;
            errflag = 1;
            s_num.push(0);
        }
    }
}

ll cal(string s, int base){
    while(!s_num.empty())s_num.pop();
    while(!s_op.empty())s_op.pop();
    s = "(" + s + ")";
    int l = s.length();
    bool last_num = 0;
    for(int i = 0; i < l; i++){
        if(isnum(s[i])){
            if(last_num)s_op.push('*');
            string sn = "";
            sn += s[i];
            int k = i;
            while(k + 1 < l && isnum(s[k + 1])){
                sn += s[k + 1];
                k++;
            }
            ll num;
            k++;
            if(s[k] == 'd') num = base2dec(10, sn);
            else if(s[k] == 'b') num = base2dec(2, sn);
            else if(s[k] == 'h') num = base2dec(16, sn);
            else if(s[k] == 'o') num = base2dec(8, sn);
            else k--, num = base2dec(base, sn);
            s_num.push(num);
            i = k;
            if(errflag){
                cout << "Invalid number" << endl;
                return 0;
            }
            last_num = 1;
        }
        else if(s[i] == '(') {
            s_op.push(s[i]);
        }
        else if(s[i] == '*' || s[i] == '/'){
            if(s_op.top() == '*' || s_op.top() == '/'){
                cal_once();
                if (errflag)return 0;
            }
            s_op.push(s[i]);
            last_num = 0;
        }
        else if(s[i] == '+' || s[i] == '-'){
            while(s_op.top() != '(') {
                cal_once();
                if (errflag)return 0;
            }
            s_op.push(s[i]);
            last_num = 0;
        }
        else if(s[i] == ')'){
            while(s_op.top() != '('){
                if(s_op.empty()){
                    cout << "Bracket mismatch" << endl;
                    errflag = 1;
                    return 0;
                }
                cal_once();
                if(errflag)return 0;
            }
            s_op.pop();
        }
        else if(s[i] != ' '){
            cout << "Invalid character" << endl;
            errflag = 1;
            return 0;
        }
    }
    if(!(s_num.size() == 1 && s_op.size() == 0)){
        errflag = 1;
        cout << "Unknown error" << endl;
        return 0;
    }
    return s_num.top();
}


void radix_main(){
    int base = 0;
    string s;
    cout << "radix mode" << endl;
    cout << "You can enter a special command right after the value to specify the numerical mode of the value. These special commands are: d (decimal), h (hexadecimal), b (binary), and o (octal)." << endl;
    cout << "Otherwise, all numbers are entered according to your specified base" << endl;
    while(true){
        cout << "input the base (2 <= base <= 16 and should be an integer)  (put 0 to exit):" << endl;
        while(getline(cin, s)){
            bool ok = 1;
            int l = s.length();
            for(int i = 0; i < l; i++)if(!isdigit(s[i]))ok = 0;
            if(ok){
                base = base2dec(10, s);
                if(base == 0)return;
                if(base >= 2 && base <= 16)break;
            }
            cout << "Invalid base" << endl;
            cout << "input the base (2 <= base <= 16 and should be an integer)  (put 0 to exit):" << endl;
        }
        errflag = 1;
        while(errflag){
            cout << "input the expression :" << endl;
            getline(cin, s);
            errflag = 0;
            ll num = cal(s, base);
            if(!errflag) cout << dec2base(base, num) << endl;
        }
    }
}
