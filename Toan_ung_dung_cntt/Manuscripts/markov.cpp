#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <iomanip>
#include <set>
using namespace std;

void printMatrix(const vector<vector<double>>& matrix) {
    cout << fixed << setprecision(2);
    for (const auto& row : matrix) {
        for (double value : row) {
            cout << value << " ";
        }
        cout << endl;
    }
}

void multiplyMatrix(const vector<vector<double>>& matrix1, const vector<vector<double>>& matrix2, vector<vector<double>>& result) {
    int n = matrix1.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            result[i][j] = 0;
            for (int k = 0; k < n; ++k) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
}

int main() {
    vector<vector<double>> P = {{0.23, 0.17, 0.33, 0.27},
                                {0.21, 0.35, 0.23, 0.21},
                                {0.18, 0.22, 0.28, 0.32},
                                {0.19, 0.37, 0.09, 0.35}};
    cout << "P:\n";
    printMatrix(P);

    vector<vector<double>> result(4, vector<double>(4, 0.0));
    vector<vector<double>> temp = P;

    int n;
    cout << "Nhap so buoc: "; cin >> n;
    for (int i = 1; i < n; ++i) {
        multiplyMatrix(temp, P, result);
        temp = result;
    }

    int start, end;
    cout << "Nhap dinh dau: "; cin >> start;
    cout << "Nhap dinh cuoi: "; cin >> end;
    cout << "Xac suat he thong o trang thai " << end
             << " sau " << n << " buoc bat dau tu trang thai " << start << " la: "
             << temp[start - 1][end - 1] << endl;
}