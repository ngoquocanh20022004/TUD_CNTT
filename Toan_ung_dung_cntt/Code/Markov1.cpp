#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <iomanip>
#include <set>

using namespace std;

vector<string> readCSV(const string& filename) {
    vector<string> foods;
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Cannot open: " << filename << endl;
        return foods;
    }
    string line;
    // Skip the header
    getline(file, line);
    while (getline(file, line)) {
        foods.push_back(line);
    }
    file.close();
    return foods;
}

void printMatrix(const vector<vector<double>>& matrix) {
    cout << fixed << setprecision(2);
    for (const auto& row : matrix) {
        for (double value : row) {
            cout << value << " ";
        }
        cout << endl;
    }
}

void countFood(vector<vector<double>>& foodCount, const map<string, int>& foodToIndex, const vector<string>& foods) {
    for (int i = 0; i < foods.size() - 1; ++i) {
        int current = foodToIndex.at(foods[i]);
        int next = foodToIndex.at(foods[i + 1]);
        foodCount[current][next] += 1;
    }
}

void normalizeMatrix(vector<vector<double>>& matrix) {
    for (auto& row : matrix) {
        double rowSum = 0;
        for (double value : row) {
            rowSum += value;
        }

        if (rowSum > 0) {
            for (double& value : row) {
                value /= rowSum;
            }
        }
    }
}

int main() {
    string filename = "breakfast.csv";
    vector<string> foods = readCSV(filename);
    if (foods.empty()) {
        return 1;
    }


    // vector<string> uniqueFoods = {"Banh mi", "Com tam", "Pho", "Sup cua"};
    set<string> uniqueFoodsSet(foods.begin(), foods.end());
    vector<string> uniqueFoods(uniqueFoodsSet.begin(), uniqueFoodsSet.end());
    map<string, int> foodToIndex;
    for (int i = 0; i < uniqueFoods.size(); i++) {
        foodToIndex[uniqueFoods[i]] = i;
    }

    int n = uniqueFoods.size();
    vector<vector<double>> foodCount(n, vector<double>(n, 0));
    countFood(foodCount, foodToIndex, foods);
    
    normalizeMatrix(foodCount);

    map<string, map<string, double>> food_pair_count;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (foodCount[i][j] > 0) {
                food_pair_count[uniqueFoods[i]][uniqueFoods[j]] = foodCount[i][j];
            }
        }
    }
    

    vector<vector<double>> transitionMatrix(n, vector<double>(n, 0.0));
    for (const auto& pair : food_pair_count) {
        vector<double> row_values;
        for (const auto& inner_pair : pair.second) {
            row_values.push_back(inner_pair.second);
        }
        transitionMatrix.push_back(row_values);
    }

    cout << "Ma tran xac suat chuyen tiep P:\n";
    printMatrix(transitionMatrix);

    string todayFood;
    cout << "\nNhap mon an sang nay: ";
    getline(cin, todayFood);

    if (foodToIndex.find(todayFood) == foodToIndex.end()) {
        cout << "Mon an khong ton tai trong du lieu.\n";
        return 1;
    }

    int todayIndex = foodToIndex[todayFood];
    cout << "Xac suat mon an sang ngay mai:\n";
    for (int j = 0; j < n; ++j) {
        cout << uniqueFoods[j] << ": " << transitionMatrix[todayIndex][j] * 100 << "%\n";
    }

    return 0;
}
