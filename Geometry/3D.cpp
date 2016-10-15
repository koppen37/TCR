struct Point {
    double x, y, z;
};

Point cartesian(double lat, double lon) {
    lat *= M_PI / 180.0, lon *= M_PI / 180.0;
    return {cos(lat) * cos(lon),
        cos(lat) * sin(lon),
        sin(lat)};
}

double magnitude(const Point &p) {
    return sqrt(p.x * p.x + p.y * p.y + p.z * p.z);
}

Point normalize(const Point &p) {
    double length = magnitude(p);
    return {p.x / length,
        p.y / length,
        p.z / length};
}

Point cross(const Point &p, const Point &q) {
    return {p.y * q.z - p.z * q.y,
        p.z * q.x - p.x * q.z,
        p.x * q.y - p.y * q.x};
}

double dot(const Point &p, const Point &q) {
    return p.x * q.x + p.y * q.y + p.z * q.z;
}

double dist(const Point &p, const Point &q) {
    return atan2(magnitude(cross(p, q)), dot(p, q));
}

Point negation(const Point &p) {
    return {-p.x, -p.y, -p.z};
}

pair<Point, Point> compute_intersections(const Point &p, const Point &q, const Point &s, const Point &t) {
    Point v1 = cross(p, q), v2 = cross(s, t),
        d = cross(v1, v2),
        first = normalize(d), second = negation(first);
    return make_pair(first, second);
}

bool on_arc(const Point &p, const Point &q, const Point &s) {
    return abs(dist(p, q) - dist(p, s) - dist(q, s)) < epsilon;
}
