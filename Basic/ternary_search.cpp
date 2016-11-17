const double epsilon = 0.000001;

double f(double x) {
    return -(x - 3) * (x - 3) + 5;
}

double ternary(double l, double r) {
    while(abs(r - l) > epsilon) {
        double lt = l + (r - l) / 3.0,
            rt = r - (r - l) / 3.0;
        // Defaults to finding maximum. Flip sign to find minimum
        f(lt) < f(rt) ? l = lt : r = rt;
    }
    return (l + r) / 2.0;
}
