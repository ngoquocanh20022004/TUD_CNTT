#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <random>
#include <iomanip>

// Đọc dữ liệu từ cột "Food" trong file CSV
class CSVReader {
    std::string filename;
public:
    CSVReader(std::string fname) : filename(fname) {}
    
    std::vector<std::string> readFoodColumn() {
        std::vector<std::string> data;
        std::ifstream file(filename);
        std::string line;
        std::getline(file, line); // Bỏ qua dòng tiêu đề
        while (std::getline(file, line)) {
            data.push_back(line);
        }
        return data;
    }
};

int main() {
    CSVReader reader("breakfast.csv");
    std::vector<std::string> data = reader.readFoodColumn();

    // Bảo toàn thứ tự món ăn
    std::vector<std::string> keys;
    std::unordered_map<std::string, int> seen;
    for (const auto& food : data) {
        if (seen.find(food) == seen.end()) {
            keys.push_back(food);
            seen[food] = 1;
        }
    }

    // Tạo ánh xạ key <-> index
    std::map<std::string, int> key_to_idx;
    for (size_t i = 0; i < keys.size(); ++i) {
        key_to_idx[keys[i]] = i;
    }

    // Khởi tạo ma trận P
    std::map<std::string, int> food_count;
    std::vector<std::vector<double>> P(keys.size(), std::vector<double>(keys.size(), 0.0));

    // Đếm số lần chuyển trạng thái
    for (size_t i = 0; i < data.size(); ++i) {
        food_count[data[i]]++;
        if (i == data.size() - 1) {
            P[key_to_idx[data[i]]][key_to_idx[data[i]]]++;
        } else {
            P[key_to_idx[data[i]]][key_to_idx[data[i + 1]]]++;
        }
    }

    // Chuẩn hóa ma trận P
    for (size_t i = 0; i < keys.size(); ++i) {
        double row_sum = 0;
        for (size_t j = 0; j < keys.size(); ++j) {
            row_sum += P[i][j];
        }
        if (row_sum > 0) {
            for (size_t j = 0; j < keys.size(); ++j) {
                P[i][j] /= row_sum;
            }
        }
    }

    // In ma trận P
    std::cout << "Ma tran chuyen trang thai P:\n";
    for (const auto& row : P) {
        for (const auto& val : row) {
            std::cout << std::fixed << std::setprecision(4) << val << " ";
        }
        std::cout << "\n";
    }

    return 0;
}
