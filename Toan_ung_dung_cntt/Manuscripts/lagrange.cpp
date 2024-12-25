#include <iostream>
#include <vector>

class LagrangeInterpolation {
private:
    std::vector<double> x_points;
    std::vector<double> y_points;

    double basicLagrange(double x, int k) {
        double result = 1.0;
        for (int i = 0; i < x_points.size(); i++) {
            if (i != k) {
                result *= (x - x_points[i]) / (x_points[k] - x_points[i]);
            }
        }
        return result;
    }

public:
    LagrangeInterpolation(const std::vector<double>& x, const std::vector<double>& y) {
        if (x.size() != y.size()) {
            throw std::invalid_argument("So diem x, y phai bang nhau");
        }
        x_points = x;
        y_points = y;
    }

    double interpolate(double x) {
        double result = 0.0;
        for (int i = 0; i < x_points.size(); i++) {
            result += y_points[i] * basicLagrange(x, i);
        }
        return result;
    }

    std::vector<double> getPolynomialCoefficients() {
        int n = x_points.size();
        std::vector<double> result(n, 0.0);

        for (int i = 0; i < n; i++) {
            std::vector<double> basic_poly = {1.0};

            for (int j = 0; j < n; j++) {
                if (j != i) {
                    std::vector<double> term = {1.0, -x_points[j]};
                    double denominator = x_points[i] - x_points[j];

                    std::vector<double> temp(basic_poly.size() + 1, 0.0);
                    for (int k = 0; k < basic_poly.size(); k++) {
                        temp[k] += basic_poly[k] / denominator;
                        temp[k + 1] += -basic_poly[k] * x_points[j] / denominator;
                    }
                    basic_poly = temp;
                }
            }

            for (int k = 0; k < basic_poly.size(); k++) {
                result[k] += y_points[i] * basic_poly[k];
            }
        }
        
        return result;
    }
};

void printPolynomial(const std::vector<double>& coeffs) {
    bool first = true;
    for (int i = coeffs.size() - 1; i >= 0; i--) {
        if (coeffs[i] == 0) continue;
        
        if (!first && coeffs[i] > 0) std::cout << "+";
        first = false;
        
        if (coeffs[i] != 1 || i == 0) {
            std::cout << coeffs[i];
        }
        if (i > 0) {
            std::cout << "x";
            if (i > 1) std::cout << "^" << i;
        }
    }
    std::cout << std::endl;
}

int main() {
    std::vector<double> x = {0, 1, 2};
    std::vector<double> y = {1, 2, 4};

    try {
        LagrangeInterpolation lagrange(x, y);

        // Tính giá trị nội suy tại x = 1.5
        double interpolated_value = lagrange.interpolate(1.5);
        std::cout << "Gia tri noi suy tai x: " << interpolated_value << std::endl;

        std::cout << "Da thuc noi suy Lagrange: ";
        std::vector<double> coeffs = lagrange.getPolynomialCoefficients();
        printPolynomial(coeffs);

    } catch (const std::exception& e) {
        std::cerr << "Loi: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}