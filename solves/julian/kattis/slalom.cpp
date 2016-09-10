#include <iostream>
#include <float.h>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

struct Point {
	long double x, y;
};

int orient(Point p, Point q, Point r) {
	long double v = (q.y - p.y) * (r.x - q.x) -
		(q.x - p.x) * (r.y - q.y);

	if(v == 0) return 0;
	return v > 0 ? 1 : -1;
}

long double dist(Point p, Point q) {
	return sqrt((p.x - q.x) * (p.x - q.x) + (p.y - q.y) * (p.y - q.y));
}

int main() {
	int n;
	while(true) {
		cin >> n;
		if(n == 0) break;
		n++;

		Point start;
		cin >> start.x >> start.y;	

		vector<vector<Point> > gates(n, vector<Point>(2));	
		gates[0][0] = start, gates[0][1] = start;

		for(int i = 1; i < n; i++) {
			cin >> gates[i][0].y
				>> gates[i][0].x
				>> gates[i][1].x;
			gates[i][1].y = gates[i][0].y;
		}

		vector<vector<long double> > DP(n, vector<long double>(2, DBL_MAX));
		DP[n - 1][0] = 0.0, DP[n - 1][1] = 0.0;

		long double a = gates[n - 1][0].x,
			b = gates[n - 1][1].x,
			fy = gates[n - 1][0].y;
		for(int i = n - 1; i >= 0; i--) {
			long double x1 = gates[i][0].x, 
				x2 = gates[i][1].x,
				y = gates[i][0].y;
			if(a <= x1 && x1 <= b) DP[i][0] = y - fy;
			if(a <= x2 && x2 <= b) DP[i][1] = y - fy;
			a = max(a, x1);
			b = min(b, x2);
		}

		for(int i = n - 2; i >= 0; i--) for(int t = 0; t < 2; t++) {
			Point s = gates[i][t],
				l = gates[i + 1][0],
				r = gates[i + 1][1];
			for(int j = i + 1; j < n; j++) {
				Point nl = gates[j][0], 
					nr = gates[j][1];
			
				if(orient(s, l, nr) > 0 || orient(s, r, nl) < 0) {
					break;
				}
				if(orient(s, l, nl) <= 0 && orient(s, r, nl) >= 0) {
					DP[i][t] = min(DP[i][t], DP[j][0] + dist(s, nl));
					l = nl;
				}
				if(orient(s, l, nr) <= 0 && orient(s, r, nr) >= 0) {
					DP[i][t] = min(DP[i][t], DP[j][1] + dist(s, nr));
					r = nr;
				}
			}
		}

		cout << setprecision(20) << DP[0][0] << endl;
	}
	
	return 0;
}
