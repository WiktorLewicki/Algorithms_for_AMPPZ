#include <bits/stdc++.h>
using namespace std;

struct Point {
    int x, y;
    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
};

Point start;

int cross_product(const Point& a, const Point& b, const Point& c) {
    int x1 = c.x - a.x, y1 = c.y - a.y;
    int x2 = b.x - a.x, y2 = b.y - a.y;
    return x1 * y2 - x2 * y1;
}

stack<Point> build_hull(vector<Point>& points) {
    stack<Point> hull;
    hull.push(points[0]);
    Point prev = points[0], curr = points[1];
    for (int i = 2; i < points.size(); i++) {
        while (cross_product(prev, curr, points[i]) >= 0) {
            curr = prev;
            hull.pop();
            if (hull.empty()) break;
            prev = hull.top();
        }
        hull.push(curr);
        prev = curr;
        curr = points[i];
    }
    return hull;
}

bool compare(const Point& a, const Point& b) {
    if (a == start) return true;
    if (b == start) return false;
    if ((a.y - start.y) * (b.x - start.x) == (a.x - start.x) * (b.y - start.y))
        return a.x < b.x;
    return (a.y - start.y) * (b.x - start.x) < (a.x - start.x) * (b.y - start.y);
}

int main() {
    int n;
    cin >> n;

    vector<Point> points(n);

    for (int i = 0; i < n; i++) {
        cin >> points[i].x >> points[i].y;
        if (i == 0 || points[i].y < start.y || 
            (points[i].y == start.y && points[i].x < start.x)) {
            start = points[i];
        }
    }

    sort(points.begin(), points.end(), compare);
    points.push_back(start);

    stack<Point> hull = build_hull(points);

    cout << start.x << ' ' << start.y << endl;
    while (!hull.empty()) {
        cout << hull.top().x << ' ' << hull.top().y << endl;
        hull.pop();
    }

    return 0;
}

