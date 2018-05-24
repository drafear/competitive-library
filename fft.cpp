typedef complex<double> C;
void dft(vector<C>& f, int s, int d, int n) {
    if (n == 1) return;
    dft(f, s, d*2, n/2);
    dft(f, s+d, d*2, n/2);
    vector<C> f0(n/2);
    vector<C> f1(n/2);
    for (int i = 0; i < f0.size(); ++i) f0[i] = f[s+2*i*d];
    for (int i = 0; i < f1.size(); ++i) f1[i] = f[s+(2*i+1)*d];
    C zeta(cos(2.0*pi/n), sin(2.0*pi/n));
    C z = 1;
    REP(i, n) {
        f[s+i*d] = f0[i % (n/2)] + z * f1[i % (n/2)];
        z *= zeta;
    }
}
void idft(vector<C>& f, int s, int d, int n) {
    if (n == 1) return;
    idft(f, s, d*2, n/2);
    idft(f, s+d, d*2, n/2);
    vector<C> f0(n/2);
    vector<C> f1(n/2);
    REP(i, f0.size()) f0[i] = f[s+2*i*d];
    REP(i, f1.size()) f1[i] = f[s+(2*i+1)*d];
    C zeta(cos(2.0*pi/n), -sin(2.0*pi/n));
    C z = C(1, 0);
    REP(i, n) {
        f[s+i*d] = f0[i % (n/2)] + z * f1[i % (n/2)];
        z *= zeta;
    }
}
int pow_2_at_least(int th) {
    int ret = 1;
    while (ret <= th) ret <<= 1;
    return ret;
}
void dft(vector<C>& f) {
    int n = pow_2_at_least(f.size() - 1);
    while (f.size() < n) f.push_back( C(0,0) );
    dft(f, 0, 1, n);
}
void idft(vector<C>& f) {
    int n = pow_2_at_least(f.size() - 1);
    while (f.size() < n) f.push_back( C(0,0) );
    idft(f, 0, 1, n);
}
vector<C> multiply(vector<C> g, vector<C> h) {
    int n = pow_2_at_least(g.size() + h.size() - 1);
    while (g.size() < n) g.push_back( C(0,0) );
    while (h.size() < n) h.push_back( C(0,0) );
    dft(g);
    dft(h);

    vector<C> f(n);
    for (int i = 0; i < n; ++i) {
        f[i] = g[i] * h[i];
    }
    idft(f);

    vector<C> ret(n);
    for (int i = 0; i < n; ++i) {
        ret[i] = f[i]/C(n,0);
    }
    return ret;
}
