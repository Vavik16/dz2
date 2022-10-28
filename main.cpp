#include <iostream>
#include <string>
#include "funcs.h"

using namespace std;

int main(){
    string l,l1;
    string res;
    cout << "Hello! Enter your equation (Remember, putting brackets leads to correct result. If you don't put brackets, program will do it automatically)" << endl;
    cout << "To use functions enter '+','-','/','*','^','sin','tg','ctg','exp','cos'" << endl;
    cin >> l;
    getline(cin,l1);
    l += l1;
    l = viewchange(l);
    if(l != "Incorrect input!") {
    res=calc(l);
    cout << "Result: " << res;
    }
    else cout << l;
}
