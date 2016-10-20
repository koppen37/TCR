// All functions should also work with other number types (doubles, floats)
struct Point {
	int x, y;
}

// Check orientation of point triplets
int orient(Point p, Point q, Point r) {
	int v = (q.y - p.y) * (r.x - q.x) -
		(q.x - p.x) * (r.y - q.y);
	if(v == 0) return 0;
	return v < 0 ? -1 : 1;
}

// Compute Euclidean distance between points
int dist(Point p, Point q) {
	return sqrt((p.x - q.x) * (p.x - q.x) + (p.y - q.y) * (p.x - q.y));
}


//Point line distance
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

//Polygon Area
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

//Rotate Point
Point rotate_point(const Point &p, const Point &c, double v) {
    double x = p.x - c.x,
        y = p.y - c.y;

    double rot_x = x * cos(v) - y * sin(v),
        rot_y = x * sin(v) + y * cos(v);

    return { rot_x + c.x, rot_y + c.y };
}

//Convex Hull
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
