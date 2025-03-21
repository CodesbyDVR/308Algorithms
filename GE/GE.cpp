#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

const double eps = 1e-9;

vector<double> ge(vector<vector<double>> A, vector<double> B) {
    int n = B.size();

    for (int i = 0; i < n; i++) {

        // for finding the pivot row , to avoid non-zero division
        int prow = i;
        for (int j = i + 1; j < n; j++) {
            if (abs(A[j][i]) > abs(A[prow][i])) {
                prow = j;
            }
        }
        // swap if i was not the pivot row we needed
        if (i != prow) {
            swap(A[i], A[prow]);
            swap(B[i], B[prow]);
        }
        // error hanlding part
                if (abs(A[i][i]) < eps) {
                    cerr << "No solution" << endl;
                    exit(EXIT_FAILURE);
                }
        
        
        for (int j = i + 1; j < n; j++) {
            // fac is the factor which will be used to make pivot col elments zero
            double fac = A[j][i] / A[i][i];
            for (int k = i; k < n; k++) {
                A[j][k] -= fac * A[i][k];
            }
            B[j] -= fac * B[i];
        }
    }

    // Back substituion on upper triangular matrix
    vector<double> x(n, 0.0);
    for (int i = n - 1; i >= 0; i--) {
        x[i] = B[i];
        for (int j = i + 1; j < n; j++) {
            x[i] -= A[i][j] * x[j];
        }
        x[i] /= A[i][i];
    }

    return x;
}

int main() {
    vector<vector<double>> A = {
        {2, 0, 0},
        {0, 3, 0},
        {0, 0, 2}
    };
    vector<double> B = {8, 13, 5};

    vector<double> x = ge(A, B);

    cout << "Solution vector x:" << endl;
    for (double val : x) {
        cout << val << " ";
    }
    cout << endl;

    return 0;
}
