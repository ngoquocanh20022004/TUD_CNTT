#include <iostream>
#include <vector>

using namespace std;

bool isPrime(long long n) {
    if (n < 2) {
        return false;
    }

    for (long long i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            return false;
        }
    }

    return true;
}
vector<long long> sieveOfEratosthenes(long long n) {

    vector<bool> isPrime(n + 1, true);
    vector<long long> primes;

    isPrime[0] = isPrime[1] = false;

    for (long long i = 2; i * i <= n; i++) {
        if (isPrime[i]) {
            for (long long j = i * i; j <= n; j += i) {
                isPrime[j] = false;
            }
        }
    }

    for (long long i = 2; i <= n; i++) {
        if (isPrime[i]) {
            primes.push_back(i);
        }
    }

    return primes;
}

long long nearestPrime(long long n) {
    long long lower = n - 1;
    long long upper = n + 1;

    while (!isPrime(lower)) {
        lower--;
    }
    while (!isPrime(upper)) {
        upper++;
    }
    return (n - lower) <= (upper - n) ? lower : upper;
}

int main() {
    long long n;

    cout << "Nhap n: ";
    cin >> n;

    vector<long long> primes = sieveOfEratosthenes(n);

    cout << "Cac so nguyen to nho hon " << n << " la: ";
    // for (long long prime : primes) {
    //     cout << prime << " ";
    // }
    cout << primes.size();
    cout << endl;

    return 0;
}
