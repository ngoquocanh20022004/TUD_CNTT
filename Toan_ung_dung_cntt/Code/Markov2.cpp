#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <iomanip>
#include <set>

using namespace std;

vector<string> readCSV(const string& filename) {
    vector<string> items;
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Cannot open: " << filename << endl;
        return items;
    }
    string line;
    getline(file, line);
    while (getline(file, line)) {
        items.push_back(line);
    }
    file.close();
    return items;
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

void multiplyMatrix(const vector<vector<double>>& matrix1, const vector<vector<double>>& matrix2, vector<vector<double>>& result) {
    int n = matrix1.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            result[i][j] = 0;
            for (int k = 0; k < n; ++k) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
}

void countTransitions(vector<vector<double>>& transitionCount, const map<string, int>& itemToIndex, const vector<string>& items) {
    for (int i = 0; i < items.size() - 1; ++i) {
        int current = itemToIndex.at(items[i]);
        int next = itemToIndex.at(items[i + 1]);
        transitionCount[current][next] += 1;
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
    string filename = "items.csv";
    vector<string> items = readCSV(filename);
    if (items.empty()) {
        return 1;
    }

    set<string> uniqueItemsSet(items.begin(), items.end());
    vector<string> uniqueItems(uniqueItemsSet.begin(), uniqueItemsSet.end());
    map<string, int> itemToIndex;
    for (int i = 0; i < uniqueItems.size(); i++) {
        itemToIndex[uniqueItems[i]] = i;
    }

    int n = uniqueItems.size();
    vector<vector<double>> transitionCount(n, vector<double>(n, 0));
    countTransitions(transitionCount, itemToIndex, items);
    
    normalizeMatrix(transitionCount);

    map<string, map<string, double>> transition_pair_count;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (transitionCount[i][j] > 0) {
                transition_pair_count[uniqueItems[i]][uniqueItems[j]] = transitionCount[i][j];
            }
        }
    }
    
    vector<vector<double>> transitionMatrix(n, vector<double>(n, 0.0));
    for (const auto& pair : transition_pair_count) {
        vector<double> row_values;
        for (const auto& inner_pair : pair.second) {
            row_values.push_back(inner_pair.second);
        }
        transitionMatrix.push_back(row_values);
    }

    cout << "Transition probability matrix P:\n";
    printMatrix(transitionMatrix);

    string currentItem;
    cout << "\nEnter the current item: ";
    getline(cin, currentItem);

    if (itemToIndex.find(currentItem) == itemToIndex.end()) {
        cout << "Item not found in the data.\n";
        return 1;
    }

    //Calculate P 50
    vector<vector<double>> transitionMatrix50 = transitionMatrix;
    for (int i = 0; i < 50; ++i) {
        vector<vector<double>> result(n, vector<double>(n, 0.0));
        multiplyMatrix(transitionMatrix50, transitionMatrix, result);
        transitionMatrix50 = result;
    }
    int currentIndex = itemToIndex[currentItem];
    cout << "Probability of the next item:\n";
    for (int j = 0; j < n; ++j) {
        cout << uniqueItems[j] << ": " << transitionMatrix[currentIndex][j] * 100 << "%\n";
    }

    return 0;
}
