#include <iostream>
#include <vector>
using namespace std;

// Hàm để kiểm tra xem một số có phải là số nguyên tố hay không
bool isPrime(int num) {
    if (num <= 1) return false;
    for (int i = 2; i * i <= num; ++i) {
        if (num % i == 0) return false;
    }
    return true;
}

vector<long long> findPerfectNumbers(long long N) {
    vector<long long> perfectNumbers;

    for (int p = 2; p < 32; ++p) {
        if (isPrime(p)) {
            long long mersenne = (1LL << p) - 1;
            long long perfect = (1LL << (p - 1)) * mersenne;

            if (perfect <= N) {
                perfectNumbers.push_back(perfect);
            }
        }
    }
    
    return perfectNumbers;
}

int main() {
    long long N = 102220002;

    vector<long long> perfectNumbers = findPerfectNumbers(N);
    cout << "Cac so hoan hao khong vuot qua " << N << " la: ";
    
    if (perfectNumbers.empty()) {
        cout << "Khong co so hoan hao nao." << endl;
    } else {
        for (long long num : perfectNumbers) {
            cout << num << " ";
        }
        cout << endl;
    }

    return 0;
}
