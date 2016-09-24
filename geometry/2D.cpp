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
