#include<bits/stdc++.h>
#define EPSILON 0.00001
#define E_VAL 2.71828
#define ALPHA 0.01
#define GAMMA 0.001
using namespace std;

double func(double x) {
    double temp1 = log10(2 * x * x + 1);
    double temp2 = exp(8 * x);
    double temp3 = 14 * x * x;
    double temp4 = 6 * x;

    double temp5 = 2 * x * x + 1;
    double temp6 = 4 * x * x;

    return ((temp1 + temp2 + temp3 - temp4) / temp5) - temp6;
}

double derivFunc(double x) {
    double temp1 = 4 * x / (2 * x * x + 1); // Đạo hàm log10
    double temp2 = 8 * exp(8 * x);          // Đạo hàm exp(8x)
    double temp3 = 28 * x;                  // Đạo hàm 14x^2
    double temp4 = 6;                       // Đạo hàm 6x
    double temp5 = 4 * x;                   // Đạo hàm (2x^2 + 1)^2
    double numerator = temp1 + temp2 + temp3 - temp4;
    double denominator = pow((2 * x * x + 1), 2);
    return numerator / denominator - 8 * x; // Gồm cả phần cuối (-4x^2)
}


void GDwithMomentum(double x, int n) {
    double velocity = 0;
    double theta = x;
    
    for (int i = 0; i < n; i++) {
        velocity = ALPHA * velocity + GAMMA * derivFunc(theta);
        theta -= velocity;

        if (abs(derivFunc(theta)) < EPSILON) {
            cout << "Do doc nho, ket thuc tai: " << i << "\n";
            break;
        }
    }

    cout << "Solution: x = " << theta << "\n";
}

int main(int argc, char const *argv[]) {
    double x0 = -2;
    int n = 10000;
    GDwithMomentum(x0, n);
    return 0;
}
