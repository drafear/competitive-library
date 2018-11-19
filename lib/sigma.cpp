// sigma[0,N) floor(n*num/den)
ll sigma(ll num, ll den, ll N) {
    if (num == 0) return 0;
    if (num >= den) {
        return num/den * N*(N-1)/2 + sigma(num%den, den, N);
    }
    else {
        ll nN = num*(N-1)/den;
        return N * (nN+1) - sigma(den, num, nN+1) - N;
    }
}
