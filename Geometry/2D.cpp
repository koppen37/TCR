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

// Given three colinear points p, q, r, the function checks if
// point q lies on line segment 'pr'
bool on_segment(Point p, Point q, Point r)
{
    if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&
        q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y))
       return true;

    return false;
}









// The main function that returns true if line segment 'p1q1'
// and 'p2q2' intersect.
bool line_intersect(Point p1, Point q1, Point p2, Point q2)
{
    // Find the four orientations needed for general and
    // special cases
    int o1 = orient(p1, q1, p2);
    int o2 = orient(p1, q1, q2);
    int o3 = orient(p2, q2, p1);
    int o4 = orient(p2, q2, q1);

    // General case
    if (o1 != o2 && o3 != o4)
        return true;

    // Special Cases
    // p1, q1 and p2 are colinear and p2 lies on segment p1q1
    if (o1 == 0 && on_segment(p1, p2, q1)) return true;

    // p1, q1 and p2 are colinear and q2 lies on segment p1q1
    if (o2 == 0 && on_segment(p1, q2, q1)) return true;

    // p2, q2 and p1 are colinear and p1 lies on segment p2q2
    if (o3 == 0 && on_segment(p2, p1, q2)) return true;

     // p2, q2 and q1 are colinear and q1 lies on segment p2q2
    if (o4 == 0 && on_segment(p2, q1, q2)) return true;

    return false; // Doesn't fall in any of the above cases
}


vector<Point> circle_intersection(Point p, Point q, double pr, double qr) {
	double d = dist(p, q);
	if(pr + qr < d) return vector<Point>(); //Snijden niet
	if(min(pr, qr) + d + epsilon < max(pr, qr)) return vector<Point>(); //Circels liggen in elkaar
	double a = (pr * pr - qr * qr + d * d) / (2.0 * d),
		h = sqrt(pr * pr - a * a);

	Point m = { p.x + (a * (q.x - p.x)) / d,
		p.y + (a * (q.y - p.y)) / d },
		r = { m.x + (h * (q.y - p.y) / d),
			m.y - (h * (q.x - p.x)) / d },
		s = { m.x - (h * (q.y - p.y) / d),
			m.y + (h * (q.x - p.x)) / d };

	return {r, s}; //Kunnen hetzelfde zijn
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
