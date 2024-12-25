#include <iostream>
#include <cmath>
using namespace std;

int calculateModule(int a, int m, int n)
{
	int result = 1;
	a %= n;

	while (m > 0) {
		if (m % 2 == 1) {
			result = (result * a) % n;
		}

		m = m >> 1;
		a = (a * a) % n;
	}

	return result;
}

int main()
{
	int a, m, n;
	cout << "Nhap a,m,n: ";
	cin >> a >> m >> n;

	cout << "Kq la: " << calculateModule(a,m,n);
	return 0;
}