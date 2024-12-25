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

bool coDoiXung(double** maTran, int n)
{
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; j++)
		{
			if (maTran[i][j] != maTran[j][i])
				return false;
		}
	}
	return true;
}

bool coXacDinhDuong(double** maTran, int n)
{
    if (!coDoiXung(maTran, n))
    {
        cout << "Ma tran khong doi xung \n";
        return false;
    }
        
    for (int i = 1; i <= n; i++)
    {
        double** temp = new double*[i];
        for(int v = 0; v < i; v++)
        {
            temp[v] = new double[i];
        }

        for (int r = 0; r < i; ++r) {
            for (int c = 0; c < i; ++c) {
                temp[r][c] = maTran[r][c];
            }
        }

        if (dinhThuc(temp, i) <= 0)
        {
            cout << "Ma tran khong co xac dinh duong\n";
            return false;
        }
            
    }
    return true;
}

double** maTranCholesky(double** maTran, int n)
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
    		temp[i][j] = 0.0;
    	}
    }

    for (int j = 0; j < n; ++j)
    {
    	for (int i = j; i < n; ++i)
    	{
    		double tong = 0;
    		if (j == i)
    		{
    			for (int k = 0; k < j; ++k)
    				tong += temp[i][k] * temp[i][k];
    			temp[j][j] = sqrt(maTran[i][j] - tong);
    			
    		}
    		else 
    		{
    			for (int k = 0; k < j; ++k)
    				tong += temp[i][k]*temp[j][k];
    			temp[i][j] = (maTran[i][j] - tong) / temp[j][j];
    		}
    	}
    }
    return temp;
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
    if (!coXacDinhDuong(A, n))
    {
        cout << "Ma tran khong the phan ra Cholesky\n";
        return 1;
    }

    double** B = maTranCholesky(A, n);
    inMaTran(B, n);

	return 0;
}