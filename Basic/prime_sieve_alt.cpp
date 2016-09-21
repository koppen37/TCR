bitset<100000010> bs; //10^8
vector<int64_t> primes; //This can blow up the memory
int64_t primes_count = 0;
int64_t sieve_size;

void sieve (int64_t n){
    sieve_size = n \;
    bs.set(); //Sets all bits in the bitset.
    bs[0] = 0, bs[1] = 0;

    //First take care of all even numbers.
    //primes.push_back(2); //Uncomment if you need a set of primes
    primes_count++;
    for(int64_t j = 2*2; j <= n; j += 2){
        bs[j] = 0;
    }
    //Now Eratosthenes sieve for other numbers.
    for(int64_t i = 3; i < sqrt(n); i++){
        if(bs[i]){
            for(int64_t j = i*i; j <= n; j += 2*i){
                bs[j] = 0;
            }
            //primes.push_back(i); //Uncomment if you need a set of primes
            primes_count++;
        }
    }
    //Now find all remaining primes below the lower bound.
    for(int64_t i = sqrt(n); i <= n; i++){
        if(bs[i]){
            //primes.push_back(i); //Uncomment if you need a set of primes
            primes_count++;
        }
    }
}

//If you have a set of primes, it can answer questions up to sieve_size^2
bool isPrime(int64_t N) {                 // a good enough deterministic prime tester
  if (N <= sieve_size) return bs[N];                   // O(1) for small primes
  for (int i = 0; i < (int)primes.size(); i++)
    if (N % primes[i] == 0) return false;
  return true;                    // it takes longer time if N is a large prime!
}                      // note: only work for N <= (last prime in vi "primes")^2

//Solved : https://open.kattis.com/problems/primesieve
