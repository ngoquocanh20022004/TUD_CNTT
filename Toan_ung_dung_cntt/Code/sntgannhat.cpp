#include <iostream>
using namespace std;

// Hàm kiểm tra số nguyên tố
bool isPrime(int n) {
    if (n <= 1) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

// Hàm tìm số nguyên tố gần nhất
int nearestPrime(int n) {
    int lower = n;
    int higher = n;

    // Tìm số nguyên tố nhỏ hơn hoặc bằng n
    while (!isPrime(lower)) {
        lower--;
    }

    // Tìm số nguyên tố lớn hơn hoặc bằng n
    while (!isPrime(higher)) {
        higher++;
    }

    // Trả về số nguyên tố gần nhất
    if ((n - lower) <= (higher - n)) {
        return lower;
    } else {
        return higher;
    }
}

int main() {
    int n;
    cout << "Nhập một số nguyên: ";
    cin >> n;

    int prime = nearestPrime(n);
    cout << "Số nguyên tố gần nhất với " << n << " là: " << prime << endl;

    return 0;
}
