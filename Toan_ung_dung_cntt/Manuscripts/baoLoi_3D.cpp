#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <cmath>
using namespace std;

struct Point {
    int x, y, z;

    Point(int x, int y, int z) : x(x), y(y), z(z) {}

    bool operator<(const Point& other) const {
        return x < other.x || (x == other.x && y < other.y) || (x == other.x && y == other.y && z < other.z);
    }
};

// Tính tích có hướng trong không gian 3D
int crossProduct(const Point& A, const Point& B, const Point& C) {
    return (B.x - A.x) * (C.y - A.y) - (B.y - A.y) * (C.x - A.x);
}

// Hàm kiểm tra chiều của ba điểm trong không gian 3D
bool counterClockWise(const Point& A, const Point& B, const Point& C) {
    return crossProduct(A, B, C) > 0;
}

vector<Point> convexHull(vector<Point> points) {
    int n = points.size();
    if (n < 3) return points;

    // Sắp xếp các điểm theo thứ tự x, rồi đến y, rồi đến z
    sort(points.begin(), points.end());

    vector<Point> hullUpper;

    for (int i = 0; i < n; i++) {
        while (hullUpper.size() >= 2 && !counterClockWise(hullUpper[hullUpper.size() - 2], hullUpper[hullUpper.size() - 1], points[i])) {
            hullUpper.pop_back();
        }
        hullUpper.push_back(points[i]);
    }

    vector<Point> hullLower;

    for (int i = n - 2; i >= 0; i--) {
        while (hullLower.size() >= 2 && !counterClockWise(hullLower[hullLower.size() - 2], hullLower[hullLower.size() - 1], points[i])) {
            hullLower.pop_back();
        }
        hullLower.push_back(points[i]);
    }

    hullUpper.insert(hullUpper.end(), hullLower.rbegin(), hullLower.rend());

    vector<Point> result;
    set<Point> seen;
    for (const Point& p : hullUpper) {
        if (seen.insert(p).second) {
            result.push_back(p);
        }
    }

    return result;
}

// Tính thể tích của polyhedron bao lồi (tạm cho 2D ở đây)
double dienTichBaoLoi(vector<Point> hull) {
    if (hull.size() < 3) return 0;

    double area = 0.0;
    for (int i = 0; i < hull.size(); i++) {
        int next = (i + 1) % hull.size();
        area += (hull[i].x * hull[next].y) - (hull[next].x * hull[i].y);
    }
    return abs(area) / 2.0;
}

int main() {
    vector<Point> points = {
        Point(-4, 2, 1), Point(-3, -2, 0), Point(-1, 4, 2), Point(-1, -4, 3),
        Point(0, 0, 0), Point(1, -2, -1), Point(1, -4, 2), Point(2, -3, 1),
        Point(3, -4, -2), Point(5, -2, 4)
    };

    vector<Point> hull = convexHull(points);

    for (Point p : hull) {
        cout << "(" << p.x << ", " << p.y << ", " << p.z << ")" << endl;
    }

    cout << "Dien tich bao loi: " << dienTichBaoLoi(hull) << endl;

    return 0;
}
