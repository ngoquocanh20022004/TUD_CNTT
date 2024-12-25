#include <iostream>
#include <cmath>
using namespace std;

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
