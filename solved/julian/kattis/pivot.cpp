#include <set>
#include <iostream>
#include <climits>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;
    
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }

    set<int> ahead(a.begin(), a.end());

    int seen = INT_MIN, ans = 0;
    for(int i = 0; i < n; i++) {
        ahead.erase(a[i]);
        if(seen < a[i] && (ahead.empty() || a[i] < *ahead.begin())) ans++;
        seen = max(seen, a[i]);
    }

    cout << ans << endl;
}
