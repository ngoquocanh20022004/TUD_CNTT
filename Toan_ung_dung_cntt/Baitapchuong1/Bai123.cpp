#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

void prime_factors(int n, vector<int>& bases, vector<int>& exponents) {
    int divisor = 2;
    while (n > 1) {
        int exponent = 0;
        while (n % divisor == 0) {
            exponent++;
            n /= divisor;
        }
        if (exponent > 0) {
            bases.push_back(divisor);
            exponents.push_back(exponent);
        }
        divisor++;
    }
}

int sum_of_divisors(int n) {
    vector<int> bases, exponents;
    prime_factors(n, bases, exponents);
    int total = 1;
    for (size_t i = 0; i < bases.size(); ++i) {
        total *= (pow(bases[i], exponents[i] + 1) - 1) / (bases[i] - 1);
    }
    return total;
}

vector<int> perfect_numbers_up_to(int n) {
    vector<int> perfect_numbers;
    for (int i = 1; i <= n; ++i) {
        if (sum_of_divisors(i) - i == i) {
            perfect_numbers.push_back(i);
        }
    }
    return perfect_numbers;
}

void sieve_of_eratosthenes(long long n) {
    vector<bool> is_prime(n + 1, true);
    is_prime[0] = is_prime[1] = false; 

    for (long long i = 2; i <= sqrt(n); ++i) {
        if (is_prime[i]) {
            for (long long j = i * i; j <= n; j += i) {
                is_prime[j] = false;
            }
        }
    }

    cout << "Cac so nguyen to <= " << n << " là:" << endl;
    for (long long i = 2; i <= 1000; ++i) {
        if (is_prime[i]) {
            cout << i << " ";
        }
    }
    cout << endl;
}

int main() {
    long long n;
    cout << "Nhap n: ";
    cin >> n;

    vector<int> bases, exponents;
    prime_factors(n, bases, exponents);

    vector<int> perfect_numbers = perfect_numbers_up_to(n);

    //Bai1
    if (!bases.empty()) {
        cout << n << " = ";
        for (size_t i = 0; i < bases.size(); ++i) {
            cout << bases[i] << "^" << exponents[i];
            if (i < bases.size() - 1) {
                cout << " * ";
            }
        }
        cout << endl;
    } else {
        cout << n << " la mot so nguyen to" << endl;
    }

    //Bai2
    if (!perfect_numbers.empty()) {
        cout << "Cac so hoan hao <= " << n << ": ";
        for (size_t i = 0; i < perfect_numbers.size(); ++i) {
            cout << perfect_numbers[i];
            if (i < perfect_numbers.size() - 1) {
                cout << ", ";
            }
        }
        cout << endl;
    } else {
        cout << "Khong co so hoan hao <= " << n << endl;
    }

    //Bai3
    long long m = 100000000;
    sieve_of_eratosthenes(m);
    return 0;
}
