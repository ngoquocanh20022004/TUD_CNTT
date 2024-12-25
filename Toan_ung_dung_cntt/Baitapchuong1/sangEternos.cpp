#include <iostream>
#include <vector>

using namespace std;

vector<int> sieveOfEratosthenes(int n) {

    vector<bool> isPrime(n + 1, true);
    vector<int> primes;

    isPrime[0] = isPrime[1] = false;

    for (int i = 2; i * i <= n; i++) {
        if (isPrime[i]) {
            for (int j = i * i; j <= n; j += i) {
                isPrime[j] = false;
            }
        }
    }

    for (int i = 2; i <= n; i++) {
        if (isPrime[i]) {
            primes.push_back(i);
        }
    }

    return primes;
}

int main() {
    int n;

    cout << "Nhap n: ";
    cin >> n;

    vector<int> primes = sieveOfEratosthenes(n);

    cout << "Cac so nguyen to nho hon " << n << " la: ";
    // for (int prime : primes) {
    //     cout << prime << " ";
    // }
    cout << primes.size();
    cout << endl;

    return 0;
}
