#include<bits/stdc++.h>
#define EPSILON 0.00001
#define E_VAL 2.71828
#define ALPHA 0.1
#define GAMMA 0.01
using namespace std;

double func(double x) {
    return 3 * exp(pow(x, 5) - pow(x, 4)) + pow(x, 2) - 20 * x + log(x + 25) - 10;
}

double derivFunc(double x) {
    double h = 1e-6;
    double dF = (func(x + h) - func(x)) / h;
    return dF;
}

double secondDerivFunc(double x) {
    double h = 1e-6;
    return (func(x + h) - 2 * func(x) + func(x - h)) / (h * h);
}

void NesterovGradientDescent(double x, int n) {
    double velocity = 0;
    double theta = x;

    for (int i = 0; i < n; i++) {
        double lookaheadTheta = theta - GAMMA * velocity;

        double grad = derivFunc(lookaheadTheta);
    
        velocity = ALPHA * velocity + GAMMA * grad;
        theta -= velocity;

        if (abs(grad) < EPSILON) {
            cout << "Dung lai o " << i << " voi do doc nho hon " << EPSILON << "\n";
            break;
        }
    }

    cout << "Solution: x = " << theta << "\n";
}

int main(int argc, char const *argv[]) {
    double x0 = 0.5;
    int n = 10000;
    NesterovGradientDescent(x0, n);
    return 0;
}
