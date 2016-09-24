#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Point {
    double x, y;

    bool operator<(const Point &rhs) const {
        return x < rhs.x || (x == rhs.x && y < rhs.y);
    }
};

int orient(Point p, Point q, Point r) {
    int v = (q.y - p.y) * (r.x - q.x) -
        (q.x - p.x) * (r.y - q.y);
    if(v == 0) return 0;
    return v < 0 ? -1 : 1;
}

vector<Point> find_points(double x, double y, double w, double h) {
    return {
        { x - w / 2, y - h / 2 }, { x - w / 2, y + h / 2 },
        { x + w / 2, y - h / 2 }, { x + w / 2, y + h / 2 }
    };
}

Point rotate_point(const Point &p, const Point &c, double v) {
    double x = p.x - c.x,
        y = p.y - c.y;

    double rot_x = x * cos(v) - y * sin(v),
        rot_y = x * sin(v) + y * cos(v);

    return { rot_x + c.x, rot_y + c.y };
}

vector<Point> convex_hull(vector<Point> ps) {
    int n = ps.size(), k = 0;
    vector<Point> hull(2 * n);

    sort(ps.begin(), ps.end());
    
    for(int i = 0; i < n; i++) {
        while(k >= 2 && orient(hull[k - 2], hull[k - 1], ps[i]) <= 0) k--;
        hull[k++] = ps[i];
    }

    for(int i = n - 2, t = k + 1; i >= 0; i--) {
        while(k >= t && orient(hull[k - 2], hull[k - 1], ps[i]) <= 0) k--;
        hull[k++] = ps[i];
    }   

    hull.resize(k - 1);
    return hull;
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
    int N;
    cin >> N;
    
    while(N--) {
        int n;
        cin >> n;

        vector<Point> ps;
        double board_area = 0.0;
        for(int i = 0; i < n; i++) {
            double x, y, w, h, v;
            cin >> x >> y >> w >> h >> v;
            board_area += w * h;
            vector<Point> new_ps = find_points(x, y, w, h);
            for(const Point &p : new_ps) {
                ps.push_back(rotate_point(p, { x, y }, -v * M_PI / 180.0));
            }
        }
        
        vector<Point> hull = convex_hull(ps);
        
        double area = polygon_area(hull),
            perc = (board_area / area) * 100.0;
        cout << fixed << setprecision(1) << perc << " %" << endl;            
    }

    return 0;
}
