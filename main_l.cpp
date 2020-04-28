#include <iostream>
#include <string>
using namespace std;

void imput(string);

int main()
{
    string line;
    while (getline(cin, line)) {
        imput(line);
    }
    return 0;
}