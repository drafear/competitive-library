ll gcd(ll a, ll b) {
  return b == 0 ? a : gcd(b, a % b);
}

struct RationalNumber {
  ll num, den;
  RationalNumber(ll num_, ll den_) {
    if (num_ == 0) {
      num = 0;
      den = 1;
    }
    else {
      num = num_/gcd(num_, den_);
      den = den_/gcd(num_, den_);
    }
  }
};
RationalNumber operator+(const RationalNumber& r1, const RationalNumber& r2) {
  return RationalNumber(r1.num * r2.den + r1.den * r2.num, r1.den * r2.den);
}
RationalNumber operator-(const RationalNumber& r1, const RationalNumber& r2) {
  return RationalNumber(r1.num * r2.den - r1.den * r2.num, r1.den * r2.den);
}
RationalNumber operator*(const RationalNumber& r1, const RationalNumber& r2) {
  return RationalNumber(r1.num * r2.num, r1.den * r2.den);
}
RationalNumber operator/(const RationalNumber& r1, const RationalNumber& r2) {
  return RationalNumber(r1.num * r2.den, r1.den * r2.num);
}
ostream& operator<<(ostream& os, const RationalNumber& r) {
  return os << r.num << " / " << r.den;
}
