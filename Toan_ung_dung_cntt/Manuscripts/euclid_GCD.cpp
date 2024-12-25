#include <iostream>
using namespace std;

int euclid(int n, int m) {
    if (m == 0) {
        return n;
    } else {
        return euclid(m, n % m);
    }
}

int main() {
    int n, m;
    cout << "Nhap n: ";
    cin >> n;
    cout << "Nhap m: ";
    cin >> m;
    cout << "UCLN cua " << n << " va " << m << " la: " << euclid(n, m) << endl;
    return 0;
}