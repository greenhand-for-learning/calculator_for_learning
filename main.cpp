#include "calculate.h"
#include <iostream>
#include <string>
using namespace std;
int main(){
    string tmp;
    while(getline(cin, tmp)){
        bool valid = true;
        double ans = calculate_with_real(tmp, valid);
        if(valid){
            cout << tmp << " = " << ans << endl;
        }
    }
    return 0;
}