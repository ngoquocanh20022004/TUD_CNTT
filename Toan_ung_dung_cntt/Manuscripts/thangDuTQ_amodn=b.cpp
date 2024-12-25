#include <iostream>
#include <vector>

using namespace std;

int extendedGCD(int a, int b, int &x, int &y) {
	if (a == 0) {
		x = 0;
		y = 1;
		return b;
	}
	int x1, y1;
	int gcd = extendedGCD(b % a, a, x1, y1);
	x = y1 - (b / a) * x1;
	y = x1;
	return gcd;
}

int modInverse(int a, int m) {
	int x, y;
	int gcd = extendedGCD(a, m, x, y);
	if (gcd != 1) {
		cout << "Nghich dao khong ton tai\n";
		return -1;
	}
	return (x % m + m) % m;
}

int thangDuTrungHoa(const vector<int>& a, const vector<int>& m) {
	int n = a.size();
	int M = 1;
	for (int i = 0; i < n; ++i) {
		M *= m[i];
	}

	int kq = 0;

	for (int i = 0; i < n; ++i) {
		int Mi = M / m[i];
		kq += a[i] * Mi * modInverse(Mi, m[i]);
		kq %= M;
	}

	return kq;
}

int main() {
	int n;
	cout << "Nhap so phuong trinh: ";
	cin >> n;
	cout << "Nhap he so va so du cua phuong trinh:\n";

	vector<int> a(n), m(n);
	for (int i = 0; i < n; ++i) {
		cin >> a[i] >> m[i];
	}

	cout << "Thang du trung hoa cua he phuong trinh la: " << thangDuTrungHoa(a, m) << endl;
}