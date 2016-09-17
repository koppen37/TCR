#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Point {
    double x, y;
};

double polygon_area(const vector<Point> &poly) {
    double area = 0.0;
    int n = poly.size();

    for(int i = 0, j = n - 1; i < n; j = i++) {
        area += (poly[j].x + poly[i].x) * (poly[j].y - poly[i].y);
    }

    return area / 2.0;
}

int main() {
    int n;
    while(cin >> n) {
        if(n == 0) break;
        vector<Point> poly(n);
        for(int i = 0; i < n; i++) cin >> poly[i].x >> poly[i].y;
        double area = polygon_area(poly);
        if(area < 0) cout << "C";
        cout << "CW " << fixed << setprecision(1) << abs(area) << endl;
    }

    return 0;
}
