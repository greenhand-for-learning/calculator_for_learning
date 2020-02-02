#include "calculate.h"
#include "statistic.h"
#include <iostream>
#include <string>
using namespace std;
int main(){
    int opt;
    cin >> opt;
    if(opt == 1){
        string tmp;
        while(getline(cin, tmp)) {
            bool valid = true;
            double ans = calculate_with_real(tmp, valid, "D");
            if (valid) {
                cout << tmp << " = " << ans << endl;
            }
        }
    }
    else if(opt == 2){

    }
    else if(opt == 3){

    }
    else if(opt == 4){

    }
    else if(opt == 5){

    }
    else if(opt == 6){
        statistic_main();
    }
    else if(opt == 7){

    }
    else if(opt == 8){

    }
    else if(opt == 9){

    }


    return 0;
}