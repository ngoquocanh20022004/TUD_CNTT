#include <iostream>
#include <vector>
#include <cmath>
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

    for (int i = n - 1; i >= 0; i--) {
        while (hullLower.size() >= 2 
        && !counterClockWise(hullLower[hullLower.size() - 2], 
                hullLower[hullLower.size() - 1], points[i])) {
            hullLower.pop_back();
        }
        hullLower.push_back(points[i]);
    }

    hullUpper.insert(hullUpper.end(), hullLower.begin(), hullLower.end());


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

double khoangCach(const Point& A, const Point& B) {
    return sqrt((A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y));
}

bool coNamTrongBaoLoi(const vector<Point>& hull, const Point& p) {
    if (hull.size() < 3) return false;

    for (int i = 0; i < hull.size(); i++) {
        int next = (i + 1) % hull.size();
        if (counterClockWise(hull[i], hull[next], p)) {
            return false;
        }
    }
    return true;
}

int main() {
    // vector<Point> points = {{-4, 2}, {-3, -2}, {-1, 4}, {-1, -4}, {0, 0}, 
    //                         {1, -2}, {1, -4}, {2, -3}, {3, -4}, {5, -2}
    // };
    vector<Point> points = {
        {6, 2}, {8, 3}, {4, 10}, {3, 5}, {16, 5}, {9, 7}, {11, 6},
        {10, 12}, {8, 9}, {7, 6}
    };
    vector<Point> hull = convexHull(points);
    cout << "Co tat ca " << hull.size() << " diem tren bao loi" << endl;
    for (Point p : hull) {
        cout << "(" << p.x << ", " << p.y << ")" << endl;
    }

    cout << "Dien tich bao loi: " << dienTichBaoLoi(hull) << endl;


    double minDistance = 1e9;
    double maxDistance = 0.0;
    for (int i = 0; i < hull.size(); i++) {
        int next = (i + 1) % hull.size();
        double distance = khoangCach(hull[i], hull[next]);  
        minDistance = min(minDistance, distance);
        maxDistance = max(maxDistance, distance);
    }

    cout << "Khoang cach nho nhat: " << minDistance << endl;
    cout << "Khoang cach lon nhat: " << maxDistance << endl;
    return 0;
}