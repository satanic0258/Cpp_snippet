// Description: 常に法を取る整数クラス。

class ModInt {
	friend std::istream& operator>>(std::istream& is, ModInt& obj);
private:
	int M;
	bool M_is_prime;
	bool isPrime() {
		for (int i = 2; i * i <= M; ++i) if (M%i == 0) return false;
		return true;
	}
public:
	int val;
	ModInt() : val(0), M(MOD), M_is_prime(true) {}
	ModInt(int n) : val(n%MOD), M(MOD), M_is_prime(true) {}
	ModInt(int n, int m) : val(n%m), M(m), M_is_prime(isPrime()) {}
	ModInt& operator=(const signed& r) {
		val = r % M;
		return *this;
	}
	ModInt operator+() const { return *this; }
	ModInt operator-() const { return ModInt(M - val); }
	ModInt& operator+=(const ModInt& r) {
		val += r.val;
		val %= M;
		return *this;
	}
	ModInt& operator+=(const int& r) {
		*this += ModInt(r);
		return *this;
	}
	ModInt& operator-=(const ModInt& r) { return *this += -r; }
	ModInt& operator-=(const int& r) { return *this += -r + M; }
	ModInt& operator++() { return *this += 1; }
	ModInt& operator++(signed tmp) { return *this += 1; }
	ModInt& operator--() { return *this -= 1; }
	ModInt& operator--(signed tmp) { return *this -= 1; }
	ModInt& operator*=(const ModInt& r) {
		val *= r.val;
		val %= M;
		return *this;
	}
	ModInt& operator*=(const int& r) {
		val *= r%M;
		val %= M;
		return *this;
	}
	ModInt& operator^=(int p) { // O(log(p))
		ModInt res(1);
		while (p) {
			if (p & 1) res *= *this;
			*this *= *this;
			p >>= 1;
		}
		return *this = res;
	}
	ModInt& operator^=(const ModInt& r) { // O(log(p))
		int p = r.val;
		return *this ^= p;
	}
	ModInt& operator/=(ModInt r) { // M must be a prime.
		assert(M_is_prime);
		return *this *= r ^= (M - 2);
	}
	ModInt& operator/=(int r) { // M must be a prime.
		return *this /= ModInt(r);
	}
	ModInt operator+(const ModInt& r) const {
		auto res(*this);
		return res += r;
	}
	ModInt operator-(const ModInt& r) const {
		auto res(*this);
		return res -= r;
	}
	ModInt operator*(const ModInt& r) const {
		auto res(*this);
		return res *= r;
	}
	ModInt operator^(const ModInt& r) const {
		auto res(*this);
		return res ^= r;
	}
	ModInt operator/(const ModInt& r) const { // M must be a prime.
		auto res(*this);
		return res /= r;
	}
	ModInt operator+(const int& r) const {
		auto res(*this);
		return res += r;
	}
	ModInt operator-(const int& r) const {
		auto res(*this);
		return res -= r;
	}
	ModInt operator*(const int& r) const {
		auto res(*this);
		return res *= r;
	}
	ModInt operator^(const int& r) const {
		auto res(*this);
		return res ^= r;
	}
	ModInt operator/(const int& r) const { // M must be a prime.
		auto res(*this);
		return res /= r;
	}
};
std::ostream& operator<<(std::ostream& os, const ModInt& obj) {
	os << obj.val;
	return os;
}
/* friend */ std::istream& operator>>(std::istream& is, ModInt& obj) {
	is >> obj.val;
	obj.val %= obj.M;
	return is;
}
/** ModInt **/