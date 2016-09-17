#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

struct Point {
    int x, y;
};

int orient(Point p, Point q, Point r) {
    int v = (q.y - p.y) * (r.x - q.x) -
        (q.x - p.x) * (r.y - q.y);
    if(v == 0) return 0;
    return v < 0 ? -1 : 1;
}

double polygon_area(const vector<Point> &poly) {
    double area = 0.0;
    int n = poly.size(),
        j = n - 1;

    for(int i = 0; i < n; i++) {
        area += (poly[j].x + poly[i].x) * (poly[j].y - poly[i].y);
        j = i;
    }

    return area / 2.0;
}

int main() {
    Point a, b, c;
    cin >> a.x >> a.y >>
        b.x >> b.y >>
        c.x >> c.y;
    
    if(orient(a, b, c) == -1) {
        Point tmp = b;
        b = c, c = tmp;
    }
    
    cout << fixed << setprecision(1) << polygon_area({ a, b, c }) << endl;

    int N, ans = 0;
    cin >> N;

    for(int i = 0; i < N; i++) {
        Point d;
        cin >> d.x >> d.y;
        if(orient(a, b, d) >= 0 &&
            orient(b, c, d) >= 0 &&
            orient(c, a, d) >= 0) ans++;        
    }

    cout << ans << endl;
}
