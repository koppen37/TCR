int pwr(int a, int b){
	int result = 1;
    while (b){
        if (b % 2) result *= a;
        b /= 2;
        a *= a;
    }

    return result;
}