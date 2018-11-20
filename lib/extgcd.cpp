ll gcd(const ll a, const ll b) {
  return b == 0 ? a : gcd(b, a % b);
}
P extgcd(const ll a, const ll b) {
  if (b == 0) return {1, 0};
  P result = extgcd(b, a % b);
  return {
    result.second,
    result.first - (a / b) * result.second,
  };
}
