#include<bits/stdc++.h>
#define EPSILON 0.0001
#define E_VAL 2.71828
#define ALPHA 0.1
#define GAMMA 0.01
using namespace std;

double F(double x) {
    return 3*exp(pow(x, 5) - pow(x, 4)) + pow(x, 2) - 20*x + log(x + 25) - 10;
}

double dF(double x) {
    double h = 1e-6;
    double dF = (F(x + h) - F(x)) / h;
    return dF;
}
double secondDerivFunc(double x) {
    double h = 1e-6;
    return (F(x + h) - 2 * F(x) + F(x - h)) / (h * h);
}

void GradientDescent(double x, int n) {
    double init = F(x);
    double h = GAMMA;
    double temp = x;

    for (int i = 0; i < n; i++) {
        temp = temp - GAMMA * dF(temp);

        init = F(temp);

        if (abs(dF(temp)) < EPSILON) {
            cout << "Dat do doc nho, ket thuc tai:  " << i << "\n";
            break;
        }
    }
    
    double result = temp;
    cout << "Giai phap: x = " << result << "\n";
    cout << "Chi phi: " << init << "\n";
    cout << "Gradient: " << dF(temp) << "\n";
}

int main(int argc, char const *argv[]) {
    double x0 = 0.5;
    int n = 10000;
    GradientDescent(x0, n);
    return 0;
}
