#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

const double eps = 1e-9;

// Function to solve Ax = B when A is a diagonal matrix
vector<double> diag(const vector<vector<double>>& A, const vector<double>& B) {
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

        // true solutions
        x[i] = B[i] / A[i][i];
    }
    
    return x;
}

int main() {
    // Example with a valid diagonal matrix
    vector<vector<double>> A = {
        {2, 0, 0},
        {0, 5, 0},
        {0, 0, 4}
    };
    vector<double> B = {4, 10, -8};

    vector<double> x = diag(A, B);

    cout << "Solution vector x:" << endl;
    for (double val : x) {
        cout << val << " ";
    }
    cout << endl;
    cout << endl;

    vector<vector<double>> A1 = {
        {1, 0, 0},
        {0, 3, 0},
        {0, 0, 0} // Zero on diagonal!
    };
    vector<double> B1 = {1, 2, 3};

    vector<double> x_singular = diag(A1, B1);

    return 0;
}
