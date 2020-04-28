//
// Created by huangb19 on 2020/2/2.
//

#include <iostream>
#include <cstdio>
#include <cmath>
#include <iomanip>
#include <cstring>

using namespace std;

int Legal_int(int d, int u){
    string s;
    while(true){
        getline(cin, s);
        int l = s.length();
        bool err = false;
        int ret = 0;
        for(int i = 0; i < l; i++){
            if(!isdigit(s[i]))err = true;
            else {
                ret = ret * 10 + (s[i] - '0');
                if(ret > u)err = true;
            }
            if(err){
                cout << "Invalid input" << endl;
                break;
            }
        }
        if(!err){
            if(ret < d)cout << "Invalid input" << endl;
            else return ret;
        }
    }
}

double Legal_double(){
    string s;
    while(true){
        getline(cin, s);
        int l = s.length(), i = 0, df = 0;
        bool err = false;
        double ret = 0, f = 1;
        if(s[0] == '-'){
            f = -1;
            i = 1;
        }
        for(; i < l; i++){
            if(s[i] == '.' && !df){
                df = 1;
            }
            else if(!isdigit(s[i]))err = 1;
            else{
                double k = s[i] - '0';
                if(!df){
                    ret = ret * 10 + k;
                    if(ret > 1e8){
                        err = 1;
                        break;
                    }
                }
                else{
                    for(int j = 1; j <= df; j++) k /= 10;
                    ret += k;
                    df ++;
                }
            }
        }
        if(err)cout << "Invalid input" << endl;
        else return ret * f;
    }
}

struct statistic_data_set{
    static const int N = 105;
    const double eps = 1e-6;
    double x[N], y[N], y_raw[N], x_raw[N], Y[N];
    int n;
    bool ok[N];
    double a, b, c, r, R2;


    void linear(){
        double sig_xy = 0, sig_x = 0, sig_y = 0, sig_x2 = 0, sig_y2 = 0;
        for(int i = 1; i <= n; i++) {
            sig_xy += x[i] * y[i];
            sig_x += x[i];
            sig_y += y[i];
            sig_x2 += x[i] * x[i];
            sig_y2 += y[i] * y[i];
        }
        a = (sig_xy - sig_x * sig_y / n) / (sig_x2 - sig_x * sig_x / n);
        b = (sig_y - a * sig_x) / n;
        r = (sig_xy * n - sig_x * sig_y) / sqrt((sig_x2 * n - sig_x * sig_x) * (sig_y2 * n - sig_y * sig_y));
    }
    void calR2(){
        double sig_y2 = 0, dif = 0;
        for(int i = 1; i <= n; i++){
            sig_y2 += y_raw[i] * y_raw[i];
            dif += (y_raw[i] - Y[i]) * (y_raw[i] - Y[i]);
        }
        R2 = (sig_y2 - dif) / sig_y2;
    }

    double det(double A[4][4]){
        return A[1][1] * (A[2][2] * A[3][3] - A[2][3] * A[3][2]) - A[1][2] * (A[2][1] * A[3][3] - A[2][3] * A[3][1]) + A[1][3] * (A[2][1] * A[3][2] - A[2][2] * A[3][1]);
    }
    void model(bool outp, int opt){
        if(opt == 1){// y=ax+b
            for(int i = 1; i <= n; i++){
                x[i] = x_raw[i];
                y[i] = y_raw[i];
            }
            linear();
            for(int i = 1; i <= n; i++){
                Y[i] = a * x_raw[i] + b;
            }
            calR2();
            if(outp)printf("y = %.4lfx + %.4lf\nr = %.4lf\nR2 = %.4lf\n\n", a, b, r, R2);
        }
        else if(opt == 2){//y=ax2+bx+c
            for(int i = 1; i <= n; i++){
                x[i] = x_raw[i];
                y[i] = y_raw[i];
            }
            double sx = 0, sy = 0, sxy = 0, sx2 = 0, sx3 = 0, sx4 = 0, sx2y = 0;
            for(int i = 1; i <= n; i++) {
                sxy += x[i] * y[i];
                sx2y += x[i] * x[i] * y[i];
                sx += x[i];
                sy += y[i];
                sx2 += x[i] * x[i];
                sx3 += x[i] * x[i] * x[i];
                sx4 += x[i] * x[i] * x[i] * x[i];
            }
            double A[4][4];
            A[1][1] = n;
            A[1][2] = A[2][1] = sx;
            A[1][3] = A[2][2] = A[3][1] = sx2;
            A[2][3] = A[3][2] = sx3;
            A[3][3] = sx4;
            double d = det(A);
            A[1][1] = sy; A[2][1] = sxy; A[3][1] = sx2y;
            c = det(A) / d;
            A[1][1] = n; A[2][1] = sx; A[3][1] = sx2;
            A[1][2] = sy; A[2][2] = sxy; A[3][2] = sx2y;
            b = det(A) / d;
            A[1][2] = sx; A[2][2] = sx2; A[3][2] = sx3;
            A[1][3] = sy; A[2][3] = sxy; A[3][3] = sx2y;
            a = det(A) / d;

            for(int i = 1; i <= n; i++){
                Y[i] = a * x_raw[i] * x_raw[i] + b * x_raw[i] + c;
            }
            calR2();
            if(outp)printf("y = %.4lfx^2 + %.4lfx + %.4lf\nR2 = %.4lf\n\n", a, b, c, R2);
        }
        else if(opt == 3){//y=alnx+b (x > 0)
            for(int i = 1; i <= n; i++){
                x[i] = log(x_raw[i]);
                y[i] = y_raw[i];
            }
            linear();
            for(int i = 1; i <= n; i++){
                Y[i] = a * x_raw[i] + b;
            }
            calR2();
            if(outp)printf("y = %.4lfln(x) + %.4lf\nR2 = %.4lf\n\n", a, b, R2);
        }
        else if(opt == 4){//y=be^(ax) (y > 0)
            for(int i = 1; i <= n; i++){
                x[i] = x_raw[i];
                y[i] = log(y_raw[i]);
            }
            linear();
            b = exp(b);
            for(int i = 1; i <= n; i++){
                Y[i] = b * exp(a * x_raw[i]);
            }
            calR2();
            if(outp)printf("y = %.4lfe^(%.4lfx)\nR2 = %.4lf\n\n", b, a, R2);
        }
        else if(opt == 5){//y=bx^a (x > 0, y > 0)
            for(int i = 1; i <= n; i++){
                x[i] = log(x_raw[i]);
                y[i] = log(y_raw[i]);
            }
            linear();
            b = exp(b);
            for(int i = 1; i <= n; i++){
                Y[i] = b * pow(x_raw[i], a);
            }
            calR2();
            if(outp)printf("y = %.4lfx^%.4lf\nR2 = %.4lf\n\n", b, a, R2);
        }
        else if(opt == 6){//y=a/x+b (x != 0)
            for(int i = 1; i <= n; i++){
                x[i] = 1.0 / x_raw[i];
                y[i] = y_raw[i];
            }
            linear();
            for(int i = 1; i <= n; i++){
                Y[i] = a / x_raw[i] + b;
            }
            calR2();
            if(outp)printf("y = %.4lf/x + %.4lf\nR2 = %.4lf\n\n", a, b, R2);
        }
    }

    void init(){
        cout << "Case    x           y" << endl;
        for(int i = 1; i <= n; i++){
            cout.precision(8); //设置输出精度，
            cout << setiosflags(ios::fixed) << setprecision(2) << setiosflags(ios::left);
            cout << setw(6) << i << setw(12) << x_raw[i] << setw(12) << y_raw[i] << endl;
            x[i] = x_raw[i]; y[i] = y_raw[i];
        }
        memset(ok, 1, sizeof(ok));
        int cnt = 0;
        for(int i = 1; i <= n; i++){
            bool dif = true;
            for(int j = 1; j < i; j++){
                if(fabs(x[i] - x[j]) <= eps)dif = false;
            }
            if(dif)cnt ++;
            if(x[i] <= eps)ok[3] = ok[5] = false;
            if(y[i] <= eps)ok[4] = ok[5] = false;
            if(fabs(x[i]) <= eps) ok[6] = false;
        }
        if(cnt == 2)ok[2] = false;
        if(cnt == 1)for(int i = 1; i <= 6; i++)ok[i] = false;
        for(int i = 1; i <= 6; i++){
            if(ok[i])model(1,i);
        }
    }
};

void statistic_main(){
    cout << "Welcome to statistic mode!" << endl;
    while(true) {
        cout << "Input the number of data:(1~100  puts 0 to exit)" << endl;
        statistic_data_set s;
        s.n = Legal_int(0, 100);
        if (s.n == 0)return;

        for (int i = 1; i <= s.n; i++) {
            cout << "Input the x of data" << i << ":\n";
            s.x_raw[i] = Legal_double();
            cout << "Input the y of data" << i << ":\n";
            s.y_raw[i] = Legal_double();
        }
        s.init();
    }
}



