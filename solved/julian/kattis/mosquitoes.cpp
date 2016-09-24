#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

struct Point {
    long double x, y;
};

long double dist(Point p, Point q) {
    return sqrt((p.x - q.x) * (p.x - q.x) + (p.y - q.y) * (p.y - q.y));
}

int trapped(const vector<Point> &ps, const Point &c, double r) {
    int res = 0;
    for(const Point &p : ps) {
        if(dist(p, c) <= r + 0.0000001) res++;
    }
    return res;
}

int main() {
    int n;
    cin >> n;

    while(n--) {
        int m;
        long double d;
        cin >> m >> d;
        long double r = d / 2.0;

        vector<Point> ps(m);
        for(int i = 0; i < m; i++) {
            cin >> ps[i].x >> ps[i].y;
        }        

        int ans = 1;

        for(int i = 0; i < m; i++) {
            for(int j = 0; j < m; j++) {
                Point p = ps[i], q = ps[j],
                    s = { (p.x + q.x) / 2.0, (p.y + q.y) / 2.0 };
                
                if(dist(p, q) < 0.000001) continue;

                long double dx = (p.x - q.x) / 2.0,
                    dy = (p.y - q.y) / 2.0,
                    dps = dist(p, s),
                    mag = sqrt(r * r - dps * dps);
                
                Point v = { dy * mag / dps, -dx * mag / dps },
                    c1 = { s.x + v.x, s.y + v.y },
                    c2 = { s.x - v.x, s.y - v.y };
                
                ans = max(ans, trapped(ps, c1, r));
                ans = max(ans, trapped(ps, c2, r));
            }
        }

        cout << ans << endl;

    }
}
