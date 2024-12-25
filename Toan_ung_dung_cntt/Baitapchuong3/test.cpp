#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

struct Point {
    int x;
    int y;

    Point(int x, int y) : x(x), y(y) {}

    bool operator<(const Point& other) const {
        return x < other.x || (x == other.x && y < other.y);
    }
};

int khoangCachManhattan(const Point& a, const Point& b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}

int khoangCachNhoNhatTraiVaPhai(vector<Point>& points, int left, int right) {
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

    sort(strip.begin(), strip.end(), [](const Point& a, const Point& b) {
        return a.y < b.y;
    });

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

int khoangCachNhoNhat(vector<Point>& points) {
    sort(points.begin(), points.end());
    return khoangCachNhoNhatTraiVaPhai(points, 0, points.size());
}

int main() {
    vector<Point> points = {
        Point(1, 2),
        Point(2, 5),
        Point(3, 4),
        Point(4, 3),
        Point(5, 4),
        Point(6, 1),
        Point(7, 5),
    };

    cout << "Khoang cach nho nhat: " << khoangCachNhoNhat(points) << endl;
    return 0;
}
