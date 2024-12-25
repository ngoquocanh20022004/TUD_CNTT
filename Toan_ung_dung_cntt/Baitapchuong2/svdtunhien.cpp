#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

typedef double** Matrix;

void nhapMaTran(Matrix maTran, int m, int n)
{
    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> maTran[i][j];
        }
    }
}

void inMaTran(Matrix maTran, int m, int n)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << maTran[i][j] << "\t\t";
        }
        cout << "\n";
    }
}

Matrix maTranChuyenVi(Matrix maTran, int m, int n)
{
    Matrix maTranChuyenVi = new double*[n];
    for (int i = 0; i < n; i++)
    {
        maTranChuyenVi[i] = new double[m];
        for (int j = 0; j < m; j++)
        {
            maTranChuyenVi[i][j] = maTran[j][i];
        }
    }
    return maTranChuyenVi;
}

Matrix nhanHaiMaTran(Matrix maTranA, Matrix maTranB, int m, int n) {
    Matrix maTranC = new double*[m];
    for (int i = 0; i < m; ++i) {
        maTranC[i] = new double[m];
        for (int j = 0; j < m; ++j) {
            maTranC[i][j] = 0;
            for (int k = 0; k < n; ++k) {
                maTranC[i][j] += maTranA[i][k] * maTranB[k][j];
            }
        }
    }
    return maTranC;
}

void phuongPhapJacobi(const Matrix maTran, double* eigenValues, Matrix eigenVectors, int n) {
    for (int i = 0; i < n; ++i) {
        eigenVectors[i][i] = 1.0;
    }

    Matrix B = maTran;
    const int lapMax = 100;

    for (int k = 0; k <= lapMax; ++k) {
        int p = 0, q = 1;
        double max = fabs(B[p][q]);
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (fabs(B[i][j]) > max) {
                    max = fabs(B[i][j]);
                    p = i;
                    q = j;
                }
            }
        }

        if (max < 1e-9) {
            break;
        }

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

        for (int i = 0; i < n; ++i) {
            eigenValues[i] = B[i][i];
        }
    }
}

void SVD (Matrix A, Matrix U, double* S, Matrix V, int m, int n) {
    Matrix AT = maTranChuyenVi(A, m, n);
    Matrix ATA = nhanHaiMaTran(AT, A, n, m);

    phuongPhapJacobi(ATA, S, V, n); 

    Matrix AV = nhanHaiMaTran(A, V, m, n);
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            U[i][j] = AV[i][j] / (S[j] + 1e-10);
        }
    }

    for (int i = 0; i < n; ++i) {
        delete[] AT[i];
        delete[] ATA[i];
    }
    delete[] AT;
    delete[] ATA;
}

int main() {
    int m, n;
    cin >> m >> n;
    
    Matrix A = new double*[m];
    for (int i = 0; i < m; ++i) {
        A[i] = new double[n];
    }
    
    Matrix U = new double*[m];
    for (int i = 0; i < m; ++i) {
        U[i] = new double[n];
    }
    
    Matrix V = new double*[n];
    for (int i = 0; i < n; ++i) {
        V[i] = new double[n];
    }
    
    double* S = new double[n];

    nhapMaTran(A, m, n);

    SVD(A, U, S, V, m, n);
    
    cout << "Matrix U:" << endl;
    inMaTran(U, m, n);

    cout << "Singular values:" << endl;
    for (int i = 0; i < n; i++) {
        cout << S[i] << " ";
    }
    cout << endl;

    cout << "Matrix V:" << endl;
    inMaTran(V, n, n);

    for (int i = 0; i < m; ++i) {
        delete[] A[i];
        delete[] U[i];
    }
    delete[] A;
    delete[] U;
    
    for (int i = 0; i < n; ++i) {
        delete[] V[i];
    }
    delete[] V;

    delete[] S;

    return 0;
}