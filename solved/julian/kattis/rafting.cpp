#include <iostream>
#include <cmath>
#include <cfloat>
#include <vector>
#include <iomanip>

using namespace std;

struct Point {
    double x, y;
};

double point_line_dist(Point p, Point q, Point r) {
    double a = p.x - q.x,
        b = p.y - q.y,
        c = r.x - q.x,
        d = r.y - q.y;

    double dot = a * c + b * d,
        mag_sq = c * c + d * d;
    
    double v = -1;
    if(mag_sq != 0) v = dot / mag_sq;

    double dx = p.x - q.x - v * c,
        dy = p.y - q.y - v * d;

    if(v < 0) dx = p.x - q.x, dy = p.y - q.y;
    if(v > 1) dx = p.x - r.x, dy = p.y - r.y;

    return sqrt(dx * dx + dy * dy);
}


int main() {
    int N;
    cin >> N;

    while(N--) {
        int ni;
        cin >> ni;
        
        vector<Point> inner(ni + 1);
        for(int i = 0; i < ni; i++) {
            cin >> inner[i].x >> inner[i].y;
        }
        inner[ni] = inner[0], ni++;

        int no;
        cin >> no;
        
        vector<Point> outer(no + 1);
        for(int i = 0; i < no; i++) {
            cin >> outer[i].x >> outer[i].y;
        }
        outer[no] = outer[0], no++;

        double narrowest = DBL_MAX;
        for(int i = 0; i < ni; i++) {
            for(int j = 0; j < no - 1; j++) {
                Point p = inner[i],
                    q = outer[j],
                    r = outer[j + 1];
                narrowest = min(narrowest, point_line_dist(p, q, r));
            }
        }
        
        for(int i = 0; i < no; i++) {
            for(int j = 0; j < ni - 1; j++) {
                Point p = outer[i],
                    q = inner[j],
                    r = inner[j + 1];
                narrowest = min(narrowest, point_line_dist(p, q, r));
            }
        }

        cout << setprecision(20) << narrowest / 2.0 << endl;
    }
    
    return 0;
}
