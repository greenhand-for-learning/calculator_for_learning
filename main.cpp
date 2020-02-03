#include "calculate.h"
#include "statistic.h"
#include "radix.h"
#include "storage.h"
#include <iostream>
#include <string>
using namespace std;
int main(){
    int opt;
    cout << "Please choose a mode. (Now only mode 1, 3 is available.)" << endl;
    cin >> opt;
    getchar();
    if(opt == 1){
        cout << "Welcome to mode 1: Calculate!" << endl;
        bool good = false;
        while(!good){
            filepath_configure(good);
        }
        check_file();
        cout << "Now you can type in your formula. Type in q to exit." << endl;
        string tmp;
        while(getline(cin, tmp)) {
            if(tmp == "q"){ break;}
            bool valid = true;
            double ans = calculate_with_real(tmp, valid, "R");
            if (valid) {
                cout << tmp << " = " << ans << endl;
            }
        }
    }
    else if(opt == 2){

    }
    else if(opt == 3){
        radix_main();
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