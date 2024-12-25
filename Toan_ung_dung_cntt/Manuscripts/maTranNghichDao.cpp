#include <iostream>
#include <cmath>
using namespace std;

void nhapMaTran(double** maTran, int n)
{
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> maTran[i][j];
        }
    }
}

void inMaTran(double** maTran, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << maTran[i][j] << "\t\t";
        }
        cout << "\n";
    }
}

void swapRows(double** maTran, int i, int j, int n)
{
    if (i != j)
    {
        for (int k = 0; k < n; k++)
        {
            double temp = maTran[i][k];
            maTran[i][k] = maTran[j][k];
            maTran[j][k] = temp;
        }
    }
}

double dinhThuc(double** maTran, int n)
{
    double det = 1.0;
    double** temp = new double*[n];
    for (int i = 0; i < n; i++)
    {
        temp[i] = new double[n];
        for (int j = 0; j < n; j++)
        {
            temp[i][j] = maTran[i][j];
        }
    }

    for (int i = 0; i < n; i++)
    {
        int k = i;
        for (; k < n; k++)
        {
            if (fabs(temp[k][i]) > 1e-9)
                break;
        }
        if (k == n)
        {
            for (int j = 0; j < n; j++)
                delete[] temp[j];
            delete[] temp;
            return 0;
        }
        if (k != i)
        {
            swapRows(temp, k, i, n);
            det = -det;
        }
        det *= temp[i][i];
        for (int j = i + 1; j < n; j++)
        {
            double factor = temp[j][i] / temp[i][i];
            for (int k = i; k < n; k++)
            {
                temp[j][k] -= factor * temp[i][k];
            }
        }
    }

    for (int i = 0; i < n; i++)
        delete[] temp[i];
    delete[] temp;

    return det;
}

double** maTranChuyenVi(double** maTran, int n)
{
    double** temp = new double*[n];
    for(int i = 0; i < n; i++)
    {
        temp[i] = new double[n];
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            temp[i][j] = maTran[j][i];
        }
    }
    return temp;
}
double** maTranCon(double** maTran, int n, int h, int c)
{
    double** B = new double*[n - 1];
    for (int i = 0; i < n - 1; i++)
    {
        B[i] = new double[n - 1];
    }

    for (int i = 0, Bi = 0; i < n; i++)
    {
        if (i == h)
            continue;
        for (int j = 0, Bj = 0; j < n; ++j)
        {
            if (j == c)
                continue;
            B[Bi][Bj] = maTran[i][j];
            ++Bj;
        }
        ++Bi;
    }

    return B;
}

double** maTranNghichDao(double** maTran, int n)
{
    double det = dinhThuc(maTran, n);
    if (det == 0) {
        cout << "Ma tran khong kha nghich" << endl;
        return nullptr;
    }

    double** maTranCV = maTranChuyenVi(maTran, n);
    double** kq = new double*[n];
    for(int i = 0; i < n; i++)
    {
        kq[i] = new double[n];
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            double detCon = dinhThuc(maTranCon(maTranCV, n, i, j), n - 1);
            inMaTran(maTranCon(maTranCV, n , i,j), n - 1);
            kq[i][j] = pow(-1, i + j) * detCon / det;
        }
    }
    return kq;
}

int main()
{
    int n;
    cin >> n;

    double** A = new double*[n];
    for (int i = 0; i < n; ++i) {
        A[i] = new double[n];
    }

    nhapMaTran(A, n);
    double** B = maTranNghichDao(A, n);
    inMaTran(B, n);

    for (int i = 0; i < n-1; ++i) {
        delete[] B[i];
    }
    delete[] B;

    for (int i = 0; i < n; ++i) {
        delete[] A[i];
    }
    delete[] A;

    return 0;
}
