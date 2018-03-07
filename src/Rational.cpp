// Description: 有理数クラス。

class Rational {
	friend std::ostream& operator<<(std::ostream& os, const Rational& obj);
private:
	ll n, d;
	inline ll gcd(ll a, ll b) { return b ? gcd(b, a%b) : a; }
	inline void reduce() {
		assert(d != 0);
		ll g = gcd(std::abs<ll>(n), std::abs<ll>(d));
		n /= g; d /= g;
		if (d < 0) {
			n *= -1;
			d *= -1;
		}
	}
public:
	Rational() : n(0), d(1) {}
	Rational(ll _n) : n(_n), d(1) {}
	Rational(ll _n, ll _d) : n(_n), d(_d) { reduce(); }
	operator double() { return 1.0*n / d; }
	bool operator<(const Rational& r) const { return n * r.d < r.n * d; }
	bool operator<=(const Rational& r) const { return !(r < *this); }
	bool operator>(const Rational& r) const { return r < *this; }
	bool operator>=(const Rational& r) const { return !(*this < r); }
	bool operator==(const Rational& r) const { return n == r.n && d == r.d; }
	bool operator==(const Rational& r) const { return !(*this == r); }
	Rational& operator=(const ll& r) { n = r; d = 1; return *this; }
	Rational operator+() const { return *this; }
	Rational operator-() const { return Rational(-n, d); }
	Rational& operator+=(const Rational& r) {
		if (d == r.d) n += r.n;
		else {
			ll g = gcd(d, r.d);
			n = n * r.d / g + r.n * d / g;
			d *= r.d / g;
			if (d < 0) { n *= -1; d *= -1; }
		}
		return *this;
	}
	Rational& operator+=(const ll& r) { n += r * d; reduce(); return *this; }
	Rational& operator-=(const Rational& r) { return *this += -r; }
	Rational& operator-=(const ll& r) { return *this += -r; }
	Rational& operator*=(const Rational& r) { n *= r.n; d *= r.d; reduce(); return *this; }
	Rational& operator*=(const ll& r) { n *= r; reduce(); return *this; }
	Rational& operator/=(const Rational& r) { return *this *= Rational(r.d, r.n); }
	Rational& operator/=(const ll& r) { return *this *= Rational(1, r); }
	Rational operator+(const Rational& r) const { return Rational(*this) += r; }
	Rational operator-(const Rational& r) const { return Rational(*this) -= r; }
	Rational operator*(const Rational& r) const { return Rational(*this) *= r; }
	Rational operator/(const Rational& r) const { return Rational(*this) /= r; }
};
/* friend */ std::ostream& operator<<(std::ostream& os, const Rational& obj) {
	os << obj.n << '/' << obj.d;
	return os;
}
/* Rational */