// Implementing newton-raphson method
#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
using namespace std;

long double fn(long double x){
    //evaluation of function value
    long double ans = 0;
    ans = pow(x , 3) - 0.165 * pow(x , 2) + 3.993 * (1e-4);
    return ans;
}

long double er(long double m , long double m1){
    long double ans = 0;
    ans = abs((m1 - m)/m1);
    return ans*100;
}