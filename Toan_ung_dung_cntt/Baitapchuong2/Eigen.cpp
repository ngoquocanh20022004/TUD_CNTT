#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

typedef vector<vector<double>> Matrix;

Matrix transpose(const Matrix& A) {
    int rows = A.size();
    int cols = A[0].size();
    Matrix AT(cols, vector<double>(rows));
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            AT[j][i] = A[i][j];
    return AT;
}

Matrix multiply(const Matrix& A, const Matrix& B) {
    int rows = A.size();
    int cols = B[0].size();
    int inner = B.size();
    Matrix C(rows, vector<double>(cols, 0.0));
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            for (int k = 0; k < inner; ++k)
                C[i][j] += A[i][k] * B[k][j];
    return C;
}

void jacobiMethod(const Matrix& A, Matrix& eigenVectors, vector<double>& eigenValues) {
    int n = A.size();
    eigenVectors = Matrix(n, vector<double>(n, 0.0));
    eigenValues = vector<double>(n, 0.0);
    
    for (int i = 0; i < n; ++i)
        eigenVectors[i][i] = 1.0;
    
    Matrix B = A;
    const int maxIterations = 100;
    const double tolerance = 1e-10;
    
    for (int iter = 0; iter < maxIterations; ++iter) {
        int p = 0, q = 1;
        double maxOffDiag = fabs(B[p][q]);
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (fabs(B[i][j]) > maxOffDiag) {
                    maxOffDiag = fabs(B[i][j]);
                    p = i;
                    q = j;
                }
            }
        }
        
        if (maxOffDiag < tolerance)
            break;
        
        double theta = (B[q][q] - B[p][p]) / (2.0 * B[p][q]);
        double t = (theta >= 0 ? 1.0 : -1.0) / (fabs(theta) + sqrt(theta * theta + 1.0));
        double c = 1.0 / sqrt(t * t + 1.0);
        double s = t * c;
        
        for (int i = 0; i < n; ++i) {
            double temp = c * B[i][p] - s * B[i][q];
            B[i][q] = s * B[i][p] + c * B[i][q];
            B[i][p] = temp;
        }
        
        for (int i = 0; i < n; ++i) {
            double temp = c * B[p][i] - s * B[q][i];
            B[q][i] = s * B[p][i] + c * B[q][i];
            B[p][i] = temp;
        }
        
        for (int i = 0; i < n; ++i) {
            double temp = c * eigenVectors[i][p] - s * eigenVectors[i][q];
            eigenVectors[i][q] = s * eigenVectors[i][p] + c * eigenVectors[i][q];
            eigenVectors[i][p] = temp;
        }
    }
    
    for (int i = 0; i < n; ++i)
        eigenValues[i] = B[i][i];
}

int main() {
    int n;
    cout << "Enter the size of the matrix (n x n): ";
    cin >> n;
    
    Matrix A(n, vector<double>(n));
    cout << "Enter the matrix elements (row by row):\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> A[i][j];
        }
    }
    
    Matrix eigenVectors;
    vector<double> eigenValues;
    
    jacobiMethod(A, eigenVectors, eigenValues);
    
    cout << "Eigenvalues:\n";
    for (double val : eigenValues) {
        cout << val << " ";
    }
    cout << endl;
    
    cout << "Eigenvectors (each row is an eigenvector):\n";
    for (const auto& row : eigenVectors) {
        for (double val : row)
            cout << val << " ";
        cout << endl;
    }
    
    return 0;
}
