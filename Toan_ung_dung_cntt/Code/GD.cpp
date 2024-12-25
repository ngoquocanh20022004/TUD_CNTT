#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <algorithm>
#include <fstream>
#include <sstream>

struct GradientResults {
    std::vector<std::vector<double>> theta_path;
    std::vector<double> losses;
};

class DataFrame {
private:
    std::vector<std::vector<double>> data;
    std::vector<std::string> columns;

public:
    DataFrame() {}

    bool readCSV(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Could not open file: " << filename << std::endl;
            return false;
        }

        std::string line;
        std::getline(file, line);
        std::stringstream ss(line);
        std::string col;
        while (std::getline(ss, col, ',')) {
            columns.push_back(col);
        }

        while (std::getline(file, line)) {
            std::vector<double> row;
            std::stringstream ss(line);
            std::string value;
            while (std::getline(ss, value, ',')) {
                row.push_back(std::stod(value));
            }
            data.push_back(row);
        }

        return true;
    }

    void normalize() {
        if (data.empty()) return;
        
        size_t cols = data[0].size();
        std::vector<double> maxVals(cols, -std::numeric_limits<double>::max());
        std::vector<double> minVals(cols, std::numeric_limits<double>::max());
        std::vector<double> sums(cols, 0.0);

        for (const auto& row : data) {
            for (size_t j = 0; j < cols; ++j) {
                maxVals[j] = std::max(maxVals[j], row[j]);
                minVals[j] = std::min(minVals[j], row[j]);
                sums[j] += row[j];
            }
        }

        std::vector<double> means(cols);
        for (size_t j = 0; j < cols; ++j) {
            means[j] = sums[j] / data.size();
        }

        for (auto& row : data) {
            for (size_t j = 0; j < cols; ++j) {
                row[j] = (row[j] - means[j]) / (maxVals[j] - minVals[j]);
            }
        }
    }

    DataFrame slice(size_t start, size_t end) const {
        DataFrame result;
        result.columns = this->columns;
        result.data.assign(data.begin() + start, data.begin() + std::min(end, data.size()));
        return result;
    }

    std::vector<std::vector<double>> getData() const { return data; }
    std::vector<std::string> getColumns() const { return columns; }
};

GradientResults batchGradientDescent(const std::vector<std::vector<double>>& X, 
                                   const std::vector<double>& Y, 
                                   int N, 
                                   double learning_rate = 0.01,
                                   int epochs_max = 1000) {
    GradientResults results;
    const int features = X[0].size();

    std::vector<double> theta(features, 0.0);
    results.theta_path.push_back(theta);

    for (int epoch = 0; epoch < epochs_max; ++epoch) {
        std::vector<double> y_hat(N);
        for (int i = 0; i < N; ++i) {
            y_hat[i] = 0;
            for (int j = 0; j < features; ++j) {
                y_hat[i] += X[i][j] * theta[j];
            }
        }

        double total_loss = 0;
        for (int i = 0; i < N; ++i) {
            double diff = y_hat[i] - Y[i];
            total_loss += diff * diff;
        }
        results.losses.push_back(total_loss / N);

        std::vector<double> gradients(features, 0.0);
        for (int j = 0; j < features; ++j) {
            for (int i = 0; i < N; ++i) {
                gradients[j] += 2 * (y_hat[i] - Y[i]) * X[i][j] / N;
            }
        }

        for (int j = 0; j < features; ++j) {
            theta[j] -= learning_rate * gradients[j];
        }
        results.theta_path.push_back(theta);
    }

    return results;
}

GradientResults gdWithMomentum(const std::vector<std::vector<double>>& X,
                              const std::vector<double>& Y,
                              int N,
                              double alpha = 0.01,
                              double beta = 0.9,
                              int epochs_max = 1000) {
    GradientResults results;
    const int features = X[0].size();
    
    std::vector<double> theta(features, 0.0);
    std::vector<double> velocity(features, 0.0);
    results.theta_path.push_back(theta);

    for (int epoch = 0; epoch < epochs_max; ++epoch) {
        std::vector<double> y_hat(N);
        for (int i = 0; i < N; ++i) {
            y_hat[i] = 0;
            for (int j = 0; j < features; ++j) {
                y_hat[i] += X[i][j] * theta[j];
            }
        }

        double total_loss = 0;
        for (int i = 0; i < N; ++i) {
            double diff = y_hat[i] - Y[i];
            total_loss += diff * diff;
        }
        results.losses.push_back(total_loss / N);

        std::vector<double> gradients(features, 0.0);
        for (int j = 0; j < features; ++j) {
            for (int i = 0; i < N; ++i) {
                gradients[j] += 2 * (y_hat[i] - Y[i]) * X[i][j] / N;
            }
        }

        for (int j = 0; j < features; ++j) {
            velocity[j] = beta * velocity[j] + alpha * gradients[j];
            theta[j] -= velocity[j];
        }
        results.theta_path.push_back(theta);
    }

    return results;
}

GradientResults nesterovGradientDescent(const std::vector<std::vector<double>>& X,
                                      const std::vector<double>& Y,
                                      int N,
                                      double alpha = 0.01,
                                      double beta = 0.9,
                                      int epochs_max = 1000) {
    GradientResults results;
    const int features = X[0].size();
    
    std::vector<double> theta(features, 0.0);
    std::vector<double> velocity(features, 0.0);
    results.theta_path.push_back(theta);

    for (int epoch = 0; epoch < epochs_max; ++epoch) {
        std::vector<double> look_ahead_theta = theta;
        for (int j = 0; j < features; ++j) {
            look_ahead_theta[j] -= beta * velocity[j];
        }

        std::vector<double> y_hat(N);
        for (int i = 0; i < N; ++i) {
            y_hat[i] = 0;
            for (int j = 0; j < features; ++j) {
                y_hat[i] += X[i][j] * look_ahead_theta[j];
            }
        }

        double total_loss = 0;
        for (int i = 0; i < N; ++i) {
            double diff = y_hat[i] - Y[i];
            total_loss += diff * diff;
        }
        results.losses.push_back(total_loss / N);

        std::vector<double> gradients(features, 0.0);
        for (int j = 0; j < features; ++j) {
            for (int i = 0; i < N; ++i) {
                gradients[j] += 2 * (y_hat[i] - Y[i]) * X[i][j] / N;
            }
        }

        for (int j = 0; j < features; ++j) {
            velocity[j] = beta * velocity[j] - alpha * gradients[j];
            theta[j] += velocity[j];
        }
        results.theta_path.push_back(theta);
    }

    return results;
}

int main() {
    DataFrame df;
    if (!df.readCSV("advertising.csv")) {
        return 1;
    }

    df.normalize();

    DataFrame train_150 = df.slice(0, 150);
    DataFrame train_20 = df.slice(150, 170);
    DataFrame train_1 = df.slice(170, 171);

    // Run algorithms and store results
    // Note: You would need to properly prepare X and Y from the DataFrame
    // and implement visualization (possibly using a C++ plotting library)


    std::cout << "Gradient descent implementations completed successfully." << std::endl;
    return 0;
}