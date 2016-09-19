vector<int> prime_sieve(int n){

	if (n < 2) return vector<int>();

	vector<int> primes;
	vector<bool> l (n+1,true);
	primes.push_back(2);

    int i = 3;
	for(; i <= sqrt(n); i += 2){
		while(!l[i]) i += 2;

		primes.push_back(i);
		for(int j=i*i; j < n; j+=i) l[j] = false;
	}

	for(; i < n; i+=2){
        if(l[i]) primes.push_back(i);
	}

	return primes;
}