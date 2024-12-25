#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

vector<int> primeFactors(int n) {
    vector<int> factors;

    while (n % 2 == 0) {
        factors.push_back(2);
        n = n / 2;
    }

    for (int i = 3; i <= sqrt(n); i = i + 2) {
        while (n % i == 0) {
            factors.push_back(i);
            n = n / i;
        }
    }

    if (n > 2) {
        factors.push_back(n);
    }
}

int phiEuler(int n) {
    vector<int> factors = primeFactors(n);
    int result = n;

    for (int i = 0; i < factors.size(); i++) {
        result -= result / factors[i];
    }

    return result;
}

int main() {
    int n;
    cin >> n;

    vector<int> factors = primeFactors(n);
    for (int i = 0; i < factors.size(); i++) {
        cout << factors[i] << " ";
    }
    cout << phiEuler(n) << endl;

    return 0;
}