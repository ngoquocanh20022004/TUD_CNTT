#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

struct Point {
    int x;
    int y;

    bool operator<(const Point& other) const {
        return x < other.x || (x == other.x && y < other.y);
    }
};

bool counterClockWise(const Point& A, const Point& B, const Point& C) {
    return (B.x * C.y - B.y * C.x) - A.x * (C.y - B.y) + A.y * (C.x - B.x) > 0;
}

vector<Point> convexHull(vector<Point> points) {
    int n = points.size();
    if (n < 3) return points;

    sort(points.begin(), points.end());

    vector<Point> hullUpper;

    for (int i = 0; i < n; i++) {
        while (hullUpper.size() >= 2 
        && !counterClockWise(hullUpper[hullUpper.size() - 2], 
                hullUpper[hullUpper.size() - 1], points[i])) {
            hullUpper.pop_back();
        }
        hullUpper.push_back(points[i]);
    }

    vector<Point> hullLower;

    for (int i = n - 2; i >= 0; i--) {
        while (hullLower.size() >= 2 
        && !counterClockWise(hullLower[hullLower.size() - 2], 
                hullLower[hullLower.size() - 1], points[i])) {
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
    vector<Point> points = {{-4, 2}, {-3, -2}, {-1, 4}, {-1, -4}, {0, 0}, 
                            {1, -2}, {1, -4}, {2, -3}, {3, -4}, {5, -2}
};
    vector<Point> hull = convexHull(points);

    for (Point p : hull) {
        cout << "(" << p.x << ", " << p.y << ")" << endl;
    }

    cout << "Dien tich bao loi: " << dienTichBaoLoi(hull) << endl;

    return 0;
}