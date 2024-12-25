#include<bits/stdc++.h>
#define EPSILON 0.00001
using namespace std;

double func(double x) {
    return 3*exp(pow(x, 5) - pow(x, 4)) + pow(x, 2) - 20*x + log(x + 25) - 10;
}

double derivFunc(double x) {
    return 3 * exp(pow(x, 5) - pow(x, 4)) * (5 * pow(x, 4) - 4 * pow(x, 3)) + 2 * x - 20 + 1/(x + 25);
}

double derivOfderivFunc(double x) {
    double term1 = 15 * exp(pow(x, 5) - pow(x, 4)) * pow(x, 3);
    double term2 = 3 * exp(pow(x, 5) - pow(x, 4)) * (5 * pow(x, 4) - 4 * pow(x, 3)) * (pow(x, 4) + 4 * pow(x, 3));
    double term3 = 9 * exp(pow(x, 5) - pow(x, 4)) * (5 * pow(x, 4) - 4 * pow(x, 3)) * pow(x, 2);
    double term4 = -1 / pow(25 + x, 2);
    return term1 + term2 + term3 + term4 + 2;
}

void newtonRaphson(double x, int n) {
    double temp = x;
    double h = 0;
    for (int i = 0; i < n; i++) {
        h = derivFunc(temp) / derivOfderivFunc(temp);
        temp = temp - h;
        if (fabs(h) < EPSILON) break;
    }
    cout << "The value of the root is : " << temp;
}

int main() {
    double x0 = 0.5;
    newtonRaphson(x0, 10000);
    return 0;
}
