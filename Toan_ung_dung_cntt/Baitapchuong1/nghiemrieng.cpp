#include <iostream>
using namespace std;

int extendedGCD(int a, int b, int& x, int &y)
{
	if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }

    int x1, y1;
    int gcd = extendedGCD(b, a % b, x1, y1);

    x = y1;
    y = x1 - (a / b) * y1;

    return gcd;
}

bool findSolution(int a, int b, int c, int& x, int&y, int& gcd)
{
	gcd = extendedGCD(abs(a), abs(b), x, y);
	if (c % gcd != 0)
	{
		return false;
	}

	x *= c / gcd;
    y *= c / gcd;

    if (a < 0) x = -x;
    if (b < 0) y = -y;

    return true;
}

int main()
{
	int a, b, c;
	cout << "ax + b = c\n";
	cout << "Nhap a, b, c: ";
	cin >> a >> b >> c;

	int x0, y0, gcd;
	if (findSolution(a,b,c,x0,y0,gcd) == true)
	{
		cout << "Nghiem tong quat: \n";
        cout << "x = " << x0 << " + r * " << b / gcd << endl;
        cout << "y = " << y0 << " - r * " << a / gcd << endl;
	}
	else 
	{
		cout << "Phuong trinh vo nghiem!";
	}
}