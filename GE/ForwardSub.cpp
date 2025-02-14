#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

const double eps = 1e-9;

// Function to perform forward substitution
vector<double> fst(const vector<vector<double>>& A, const vector<double>& B) {
    int n = B.size();
    vector<double> x(n, 0.0);

    for (int i = 0; i < n; i++) {
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
        for (int j = 0; j < i; j++) {
            x[i] -= A[i][j] * x[j];
        }
        x[i] /= A[i][i];
    }
    
    return x;
}

int main() {
    // Example with a valid lower triangular matrix
    vector<vector<double>> A = {
        {2, 0, 0},
        {3, 5, 0},
        {1, -2, 4}
    };
    vector<double> B = {4, 7, -3};

    vector<double> x = fst(A, B);

    cout << "Solution vector x:" << endl;
    for (double val : x) {
        cout << val << " ";
    }
    cout << endl;
    cout << endl;

    // Trying for matrix which might not have a solution
    vector<vector<double>> A1 = {
        {1, 0, 0},
        {2, 3, 0},
        {4, 5, 0}
    };
    vector<double> B1 = {1, 2, 3};

    vector<double> x_singular = fst(A1, B1);
    return 0;
}
