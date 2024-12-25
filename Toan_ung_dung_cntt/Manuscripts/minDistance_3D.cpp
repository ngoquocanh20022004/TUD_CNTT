#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <cmath>

using namespace std;

struct Point {
    int x;
    int y;
    int z;

    Point(int x, int y, int z) : x(x), y(y), z(z) {}
    bool operator<(const Point& other) const {
        return x < other.x || (x == other.x && y < other.y) || (x == other.x && y == other.y && z < other.z);
    }
};

int khoangCachManhattan(const Point& a, const Point& b) {
    return abs(a.x - b.x) + abs(a.y - b.y) + abs(a.z - b.z);
}

double khoangCachEuclid(const Point& a, const Point& b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2) + pow(a.z - b.z, 2));
}


double khoangCachCosin(const Point& a, const Point& b) {
    double dotProduct = a.x * b.x + a.y * b.y + a.z * b.z;
    double magnitudeA = sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
    double magnitudeB = sqrt(b.x * b.x + b.y * b.y + b.z * b.z);
    return dotProduct / (magnitudeA * magnitudeB);
}

double khoangCachMinkowski(const Point& a, const Point& b, int p) {
    return pow(pow(abs(a.x - b.x), p) + pow(abs(a.y - b.y), p) + pow(abs(a.z - b.z), p), 1.0 / p);
}

int khoangCachChebyshev(const Point& a, const Point& b) {
    return max({abs(a.x - b.x), abs(a.y - b.y), abs(a.z - b.z)});
}


int khoangCachHamming(const Point& a, const Point& b) {
    int diff = 0;
    diff += (a.x != b.x);
    diff += (a.y != b.y);
    diff += (a.z != b.z);
    return diff;
}

int khoangCachNhoNhatTraiVaPhai(vector<Point> &points, int left, int right) {
    if (right - left <= 1) {
        return INT_MAX;
    }

    int mid = left + (right - left) / 2;
    int minLeft = khoangCachNhoNhatTraiVaPhai(points, left, mid);
    int minRight = khoangCachNhoNhatTraiVaPhai(points, mid, right);

    int minDistance = min(minLeft, minRight);

    vector<Point> strip;
    for (int i = left; i < right; i++) {
        if (abs(points[i].x - points[mid].x) < minDistance) {
            strip.push_back(points[i]);
        }
    }

    for (int i = 0; i < strip.size(); i++) {
        for (int j = i + 1; j < strip.size(); j++) {
            if (abs(strip[j].y - strip[i].y) >= minDistance) {
                break;
            }
            
            minDistance = min(minDistance, khoangCachManhattan(strip[i], strip[j]));
        }
    }

    return minDistance;
}

int khoangCachNhoNhat(vector<Point> &points) {
    sort(points.begin(), points.end());

    return khoangCachNhoNhatTraiVaPhai(points, 0, points.size());
}

int main() {
    vector<Point> points = {
        Point(1, 2, 3),
        Point(4, 5, 6),
        Point(7, 8, 9),
        Point(1, 1, 1),
        Point(7, 2, 3),
        Point(2, 2, 2),
        Point(3, 3, 3),
    };
    cout << khoangCachNhoNhat(points) << endl;

    return 0;
}