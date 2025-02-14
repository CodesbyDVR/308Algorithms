#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

const double eps = 1e-9;

vector<double> ge(vector<vector<double>> A, vector<double> B) {
    int n = B.size();

    for (int i = 0; i < n; i++) {
        int prow = i;
        for (int j = i + 1; j < n; j++) {
            if (abs(A[j][i]) > abs(A[prow][i])) {
                prow = j;
            }
        }
        if (i != prow) {
            swap(A[i], A[prow]);
            swap(B[i], B[prow]);
        }

        if (abs(A[i][i]) < eps) {
            cerr << "No solution" << endl;
            exit(EXIT_FAILURE);
        }
        for (int j = i + 1; j < n; j++) {
            double factor = A[j][i] / A[i][i];
            for (int k = i; k < n; k++) {
                A[j][k] -= factor * A[i][k];
            }
            B[j] -= factor * B[i];
        }
    }

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
        {2, -1, 1},
        {1, 3, 2},
        {1, -1, 2}
    };
    vector<double> B = {8, 13, 5};

    vector<double> x = ge(A, B);

    cout << "Solution vector x:" << endl;
    for (double val : x) {
        cout << val << " ";
    }
    cout << endl;

    vector<vector<double>> A1 = {
        {1, 2, 3},
        {2, 4, 6},
        {3, 6, 9}
    };
    vector<double> B1 = {6, 12, 18};
    vector<double> x_singular = ge(A1, B1);

    return 0;
}
