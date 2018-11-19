int gcd(const int a, const int b) {
    return b == 0 ? a : gcd(b, a % b);
}
pair<int, int> extgcd(const int a, const int b) {
    if (b == 0) return {1, 0};
    pair<int, int> result = extgcd(b, a % b);
    return {
        result.second,
        result.first - (a / b) * result.second,
    };
}
