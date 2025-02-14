#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

const double eps = 1e-9;

vector<double> bst(const vector<vector<double>>& A, const vector<double>& B) {
    int n = B.size();
    vector<double> x(n, 0.0);

    for (int i = n - 1; i >= 0; i--) {
        // checking if the diagonal element is too small , or zero
        if (abs(A[i][i]) < eps) {
            cerr << "Error: Singular matrix detected (zero on diagonal at row " << i << ")." << endl;

            // Checking if the B[i] is also 0, meaning an infinite solutions case
            if (abs(B[i]) < eps) {
                cerr << "inf solutions" << endl;
            } else {
                cerr << "No solution" << endl;
            }
            exit(EXIT_FAILURE);
        }

        // Compute the current x[i] value
        x[i] = B[i];
        for (int j = i + 1; j < n; j++) {
            x[i] -= A[i][j] * x[j];
        }
        x[i] /= A[i][i];
    }
    
    return x;
}

int main() {
    // Example
    vector<vector<double>> A = {
        {2, 3, -1},
        {0, 5, 2},
        {0, 0, 4}
    };
    vector<double> B = {5, 3, -2};

    vector<double> x = bst(A, B);

    cout << "Solution vector x:" << endl;
    for (double val : x) {
        cout << val << " ";
    }
    cout << endl;
    cout << endl;
    cout << endl;


    vector<vector<double>> singularA = {
        {1, 2, 3},
        {0, 4, 5},
        {0, 0, 0} 
    };
    vector<double> singularB = {6, 7, 8};
    vector<double> x_singular = bst(singularA, singularB);

    return 0;
}
