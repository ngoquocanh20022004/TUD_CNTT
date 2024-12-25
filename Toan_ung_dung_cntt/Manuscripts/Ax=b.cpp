#include <iostream>
#include <cmath>
#include <iomanip>
#include "maTranNghichDao.cpp"
using namespace std;

double* nhanMaTranVoiVector(double** A, double* b, int n) {
    double* result = new double[n];
    for(int i = 0; i < n; i++) {
        result[i] = 0;
        for(int j = 0; j < n; j++) {
            result[i] += A[i][j] * b[j];
        }
    }
    return result;
}

double* giaiPTGauss(double** A, double* b, int n) {
    double** aug = new double*[n];
    for(int i = 0; i < n; i++) {
        aug[i] = new double[n + 1];
        for(int j = 0; j < n; j++)
            aug[i][j] = A[i][j];
        aug[i][n] = b[i];
    }

    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            double ratio = aug[j][i] / aug[i][i];
            for(int k = i; k <= n; k++)
                aug[j][k] -= ratio * aug[i][k];
        }
    }

    double* x = new double[n];
    for(int i = n - 1; i >= 0; i--) {
        x[i] = aug[i][n];
        for(int j = i + 1; j < n; j++)
            x[i] -= aug[i][j] * x[j];
        x[i] /= aug[i][i];
    }

    for(int i = 0; i < n; i++)
        delete[] aug[i];
    delete[] aug;

    return x;
}

int main() {
    int n;
    cout << "Nhap kich thuoc ma tran: ";
    cin >> n;

    double** A = new double*[n];
    double* b = new double[n];
    for(int i = 0; i < n; i++)
        A[i] = new double[n];

    cout << "Nhap ma tran A:\n";
    nhapMaTran(A, n);

    cout << "Nhap vector b:\n";
    for(int i = 0; i < n; i++)
        cin >> b[i];

    cout << "\nNghiem bang phuong phap nghich dao:\n";
    double** A_inv = maTranNghichDao(A, n);
    double* x_inv = nhanMaTranVoiVector(A_inv, b, n);
    for(int i = 0; i < n; i++)
        cout << "x[" << i << "] = " << fixed << setprecision(4) << x_inv[i] << endl;

    cout << "\nNghiem bang phuong phap Gauss:\n";
    double* x_gauss = giaiPTGauss(A, b, n);
    for(int i = 0; i < n; i++)
        cout << "x[" << i << "] = " << fixed << setprecision(4) << x_gauss[i] << endl;

    for(int i = 0; i < n; i++) {
        delete[] A[i];
    }
    delete[] A;
    delete[] A_inv;
    delete[] b;
    delete[] x_inv;
    delete[] x_gauss;

    return 0;
}