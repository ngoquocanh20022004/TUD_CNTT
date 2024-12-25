#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

bool isPerfectNum(long long n) {
    if (n <= 1) return false;

    long long sum = 1;

    for (long long i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) {
            sum += i;
            if (i != n / i) {
                sum += n / i;
            }
        }
    }

    return sum == n;
}