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

void bisection(long double r , long double tol){
    long double u = 2*r;
    long double l = 0;
    long double m = (u + l)/2;
    cout << setw(10) << l
             << setw(10) << u
             << setw(10) << m
             << setw(15)  << "-"
             << setw(15)  << fn(m) << endl;
    int k = 0;
    // cout << fn(m)*fn(l) << endl;
    // there is a fucntion 
    if(fn(u)*fn(l) < 0){
            // cout << "HI\n";
            if(fn(m)*fn(u) < 0) l = m;
            else if(fn(m)*fn(l) < 0 ) u = m;            
        }
    // cout << u << " " << l << endl;
    while(l<=u){
        if(fn(u)*fn(l) < 0){
            long double m1 = (u + l)/2;
            // cout << "HI\n";
            
            cout << setw(10) << l
             << setw(10) << u
             << setw(10) << m1
             << setw(10)  << er(m,m1) << "%  "
             << setw(15)  << fn(m1) << endl;
            

            if(fn(m1)*fn(u) < 0) l = m1;
            else if(fn(m1)*fn(l) < 0 ) u = m1;


            if(er(m,m1) < tol) return;
            k++;
            if(k > 8) return;
            m = m1;
        }
    }
}

int main(){
    // radius of cylinder question
    long double rad = 0.055;
    long double tol = 1e-5;
    // cout << tol << endl;

    cout << left << setw(10) << "l"
         << setw(10) << "u"
         << setw(10) << "m1"
         << setw(15) << "er(%)"
         << setw(15) << "fn(m1)" << endl;
    cout << string(55, '-') << endl;

    bisection(rad , tol);

    // cout << fixed << setprecision(30) << fn(0.0624121) << endl;
    return 0;
}