#include <iostream>
#include <bitset>
#include <map>

using namespace std;

// Struct that defines ordering for map memoization
// Sort descending by position of lowest bit
struct ordering {
    bool operator()(const bitset<72>& lhs, const bitset<72>& rhs) const {
	    for (int i = 71; i >= 0; i--) {
	        if (lhs[i] ^ rhs[i]) return rhs[i];
	    }
	    return false;
	}
};

int n, m;

// Memoization map, using ordering as defined above
map<bitset<72>, int64_t, ordering> mem;

// Dynamic programming recursion
int64_t dp(bitset<72> bs, int p) {

	// First check if this state is in memory
	map<bitset<72>, int64_t>::iterator it = mem.find(bs);
	if(it != mem.end()) return it->second;

	// Find the next set bit, going as far right and up
	// as possible until we get to the top-left corner
	while(!bs.test(p) && p > 0) {
		p < 24 ? p += 47 : p -= 24;
	}

	// Reached top-left corner, base case
	if(p == 0) return 1;

	int64_t res = 0;

	// Unset current bit (1x1 block placement)	
	bs.flip(p);
	res += dp(bs, p);
	
	// If bit above is in bounds and alive, place
	// place a 1x2 block instead of a 1x1
	if(p >= 24 && bs.test(p - 24)) {
		bs.flip(p - 24);
		res += dp(bs, p);
		bs.flip(p - 24);
	}

	// If bit to the left is in bounds and alive,
	// place a 2x1 block instead of a 1x1
	if(p % 24 != 0 && bs.test(p - 1)) {
		bs.flip(p - 1);
		res += dp(bs, p);
		bs.flip(p - 1);
	}

	// Reset to original bitboard and store result
	// in memory before returning
	bs.flip(p);
	mem[bs] = res;
	return res;
}

int main() {
    cin >> m >> n;

    // Represent tray as 3x24 (72) bitboard
    bitset<72> bs;

    // Set only the 3xM section of the board
    for(int i = 0; i < m; i++) for(int j = 0; j < 3; j++) {
    	bs.set(i + j * 24);
    }

    // Unset the dead points
    for(int i = 0; i < n; i++) {
        double x, y;
        cin >> x >> y;
        bs.set((int)x + (int)y * 24, 0);
    }

    // Get the answer for the full board, with the
    // pointer starting in the bottom-right
    cout << dp(bs, m + 47) << endl; 

    return 0;
}
