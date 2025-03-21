#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

// Function to perform LU Decomposition with Partial Pivoting
bool luDecomposition(vector<vector<double>>& A, vector<vector<double>>& L, vector<vector<double>>& U, vector<vector<double>>& P) {
    int n = A.size();

    // Initialize L, U, and P matrices
    for (int i = 0; i < n; i++) {
        L[i][i] = 1.0;
        P[i][i] = 1.0;
    }

    for (int k = 0; k < n; k++) {
        // Partial Pivoting: Find the row with the maximum element in column k
        int maxRow = k;
        for (int i = k + 1; i < n; i++) {
            if ( A[maxRow][k] == 0 && abs(A[i][k]) > abs(A[maxRow][k])) {
                maxRow = i;
            }
        }
        // cout << '\n' << maxRow << '\n' ;

        // Swap rows in A, P, and L (up to the current column)
        if (maxRow != k) {
            swap(A[k], A[maxRow]);
            swap(P[k], P[maxRow]);
            // swapping for corresponding changes in L matrix
            if (k > 0) {
                for (int i = 0; i < k; i++) {
                    swap(L[k][i], L[maxRow][i]);
                }
            }
        }

        // Check for zero or near-zero pivot , to avoid division by zero
        if (abs(A[k][k]) < 1e-9) {
            cout << "Zero pivot detected. LU Decomposition failed." << endl;
            return false;
        }

        // Filling U matrix (which is essentially the changes made for A )
        for (int j = k; j < n; j++) {
            U[k][j] = A[k][j];
        }
        // calculate multipliers for L , to replace the positions , corresponding to A , but in identity L
        for (int i = k + 1; i < n; i++) {
            L[i][k] = A[i][k] / A[k][k];
            for (int j = k; j < n; j++) {
                A[i][j] -= L[i][k] * A[k][j];
            }
        }
    }

    return true;
}

// Function to print matrix
void printMatrix(const vector<vector<double>>& M) {
    int n = M.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << setw(10) << fixed << setprecision(2) << M[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    // Example matrix A
    vector<vector<double>> A = {
        // {1, 2, 1, 3},
        // {2, 4, 1, 5},
        // {3, 2, 1, 4},
        // {4, 1, 1, 3}
        // {1,2,1},
        // {2,4,1},
        // {3,2,1}
        {2,0,1},
        {4,3,2},
        {6,0,5}


    };
    int n = A.size();
    cout << "Input Matrix A:\n";
    printMatrix(A);

    // Initialize L, U, and P matrices
    vector<vector<double>> L(n, vector<double>(n, 0));
    vector<vector<double>> U(n, vector<double>(n, 0));
    vector<vector<double>> P(n, vector<double>(n, 0));

    // Perform LU Decomposition with Partial Pivoting
    if (luDecomposition(A, L, U, P)) {
        cout << "\nMatrix L:\n";
        printMatrix(L);

        cout << "\nMatrix U:\n";
        printMatrix(U);

        cout << "\nPermutation Matrix P:\n";
        printMatrix(P);
    } else {
        cout << "LU Decomposition failed due to zero pivot.\n";
    }

    return 0;
}
