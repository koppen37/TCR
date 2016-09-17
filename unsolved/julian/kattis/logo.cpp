#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int main() {
    int N;
    cin >> N;

    while(N--) {
        int n;
        cin >> n;
        
        long double x = 0.0,
            y = 0.0,
            v = 0.0;

        while(n--) {
            string cmd;
            long double val;
            cin >> cmd >> val;
            
            if(cmd == "fd") {
                x += cos(v * M_PI / 180.0) * val;
                y += sin(v * M_PI / 180.0) * val;
            } else if(cmd == "bk") {
                x -= cos(v * M_PI / 180.0) * val;
                y -= sin(v * M_PI / 180.0) * val;
            } else if(cmd == "lt") {
                v += val;
            } else {
                v -= val;
            }
        }

        cout << round(sqrt(x * x + y * y)) << endl;
    }

    return 0;
}
