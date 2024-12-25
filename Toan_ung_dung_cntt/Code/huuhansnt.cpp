#include <iostream>
#include <cmath>
using namespace std;
void factor(int n)
{
    for (int i = 2; i <= sqrt(n); i++)
    {
        int mu = 0;
        while (n % i == 0)
        {
            n /= i;
            mu++;
        }
        if (mu != 0)
        {
            cout << i << "^" << mu;
            if (n > 1)
            {
                cout << " x ";
            }
        }
    }
    if (n > 1)
    {
        cout << n;
    }
}
int main()
{
    int a;
    cout << "Nhap N = ";
    cin >> a;
    factor(a);
    return 0;
}