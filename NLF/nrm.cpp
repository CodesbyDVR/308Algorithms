#include <iostream>
#include <vector>
#include <cmath>
#include <limits>

using namespace std;

// Function prototypes
void newtonRaphson(vector<double> (*F)(vector<double>), vector<vector<double>> (*J)(vector<double>), vector<double> &X, int maxIter = 100, double tol = 1e-6);
vector<double> solveLinearSystem(vector<vector<double>> A, vector<double> B);
double determinant(vector<vector<double>> A);

// Example system of nonlinear equations
vector<double> F(vector<double> X) {
    double x = X[0], y = X[1], z = X[2];
    return { x*x + y*y + z*z - 4, 
             x*y - 1, 
             x + y + z - 3 };
}

// Jacobian matrix
vector<vector<double>> J(vector<double> X) {
    double x = X[0], y = X[1], z = X[2];
    return { { 2*x, 2*y, 2*z },
             { y, x, 0 },
             { 1, 1, 1 } };
}

// Newton-Raphson solver
void newtonRaphson(vector<double> (*F)(vector<double>), vector<vector<double>> (*J)(vector<double>), vector<double> &X, int maxIter, double tol) {
    int n = X.size();
    double alpha = 1.0;  // Damping factor

    for (int iter = 0; iter < maxIter; iter++) {
        vector<double> F_val = F(X);
        vector<vector<double>> J_val = J(X);

        // Check function tolerance
        double maxError = 0;
        for (double f : F_val) maxError = max(maxError, fabs(f));
        if (maxError < tol) {
            cout << "Solution found after " << iter + 1 << " iterations:\n";
            for (int i = 0; i < n; i++) 
                cout << "x" << i + 1 << " = " << X[i] << endl;
            return;
        }

        // Check Jacobian determinant
        double detJ = determinant(J_val);
        if (fabs(detJ) < 1e-10) {
            cerr << "Error: Jacobian matrix is nearly singular! Adjust initial guess.\n";
            exit(1);
        }

        // Solve J * delta_X = -F
        vector<double> delta_X = solveLinearSystem(J_val, F_val);
        
        // Update X using damping factor
        for (int i = 0; i < n; i++) X[i] -= alpha * delta_X[i];
    }

    cout << "Newton-Raphson did not converge after " << maxIter << " iterations.\n";
}

// Solves Ax = b using Gaussian elimination with **Partial Pivoting**
vector<double> solveLinearSystem(vector<vector<double>> A, vector<double> B) {
    int n = A.size();

    for (int i = 0; i < n; i++) {
        // **Partial Pivoting**
        int maxRow = i;
        for (int k = i + 1; k < n; k++)
            if (fabs(A[k][i]) > fabs(A[maxRow][i]))
                maxRow = k;
        swap(A[i], A[maxRow]);
        swap(B[i], B[maxRow]);

        // Check for zero pivot
        if (fabs(A[i][i]) < numeric_limits<double>::epsilon()) {
            cerr << "Error: Singular Jacobian Matrix (division by zero detected)\n";
            exit(1);
        }

        // Eliminate column
        for (int k = i + 1; k < n; k++) {
            double factor = A[k][i] / A[i][i];
            for (int j = i; j < n; j++) A[k][j] -= factor * A[i][j];
            B[k] -= factor * B[i];
        }
    }

    // **Back-substitution**
    vector<double> X(n, 0);
    for (int i = n - 1; i >= 0; i--) {
        X[i] = B[i];
        for (int j = i + 1; j < n; j++) X[i] -= A[i][j] * X[j];
        X[i] /= A[i][i];
    }
    return X;
}

// Computes determinant using **Row Reduction**
double determinant(vector<vector<double>> A) {
    int n = A.size();
    double det = 1;
    for (int i = 0; i < n; i++) {
        if (fabs(A[i][i]) < numeric_limits<double>::epsilon()) return 0;
        det *= A[i][i];
    }
    return det;
}

int main() {
    vector<double> X = {0.5, 1.5, 1.0}; // Initial guess
    newtonRaphson(F, J, X);
    return 0;
}
