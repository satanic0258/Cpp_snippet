// Description: 加法をXOR、乗法をANDとした行列演算ライブラリ。

// + -> XOR, * -> AND
using BIT_TYPE_Matrix_XOR_AND = unsigned; // [unsigned] or [unsigned long long]
constexpr size_t MAX_BIT_Matrix_XOR_AND = 32; // if BIT_TYPE is [unsigned long long] then 64
class Matrix_XOR_AND {
private:
	std::valarray<std::valarray<BIT_TYPE_Matrix_XOR_AND>> mat;
public:
	Matrix_XOR_AND(size_t m = 0, size_t n = 0, BIT_TYPE_Matrix_XOR_AND init = 0) {
		if (n == 0) n = m;
		mat.resize(m);
		for (size_t i = 0; i < m; ++i) mat[i].resize(n, init);
	}
	Matrix_XOR_AND(std::valarray<std::valarray<BIT_TYPE_Matrix_XOR_AND>> a) { mat = a; }
	Matrix_XOR_AND init(size_t m = 0, size_t n = 0, BIT_TYPE_Matrix_XOR_AND init = 0) {
		if (n == 0) n = m;
		mat.resize(m);
		for (size_t i = 0; i < m; ++i) mat[i].resize(n, init);
		return *this;
	}
	std::valarray<BIT_TYPE_Matrix_XOR_AND>& operator[](size_t i) { return mat[i]; }
	const std::valarray<BIT_TYPE_Matrix_XOR_AND>& operator[](size_t i) const { return mat[i]; }
	Matrix_XOR_AND& operator=(const Matrix_XOR_AND& r) {
		for (size_t i = 0; i < mat.size(); ++i) mat[i] = r[i];
		return *this;
	}
	Matrix_XOR_AND& operator+=(const Matrix_XOR_AND& r) {
		for (size_t i = 0; i < mat.size(); ++i) mat[i] ^= r[i];
		return *this;
	}
	Matrix_XOR_AND& operator+=(const BIT_TYPE_Matrix_XOR_AND& x) {
		for (size_t i = 0; i < mat.size(); ++i) mat[i] ^= x;
		return *this;
	}
	Matrix_XOR_AND& operator*=(const Matrix_XOR_AND& r) { // O(N^3)
		Matrix_XOR_AND res(mat.size(), r[0].size());
		for (size_t i = 0; i < mat.size(); ++i) {
			for (size_t j = 0; j < r[0].size(); ++j) {
				for (size_t k = 0; k < mat[0].size(); ++k) {
					res[i][j] ^= mat[i][k] & r[k][j];
				}
			}
		}
		return *this = res;
	}
	Matrix_XOR_AND& operator*=(const BIT_TYPE_Matrix_XOR_AND& x) {
		for (size_t i = 0; i < mat.size(); ++i) mat[i] &= x;
		return *this;
	}
	Matrix_XOR_AND& operator^=(ll p) { // O(N^3 logP)
		Matrix_XOR_AND res(mat.size());
		--p;
		res = (*this);
		while (p) {
			if (p & 1) res *= (*this);
			(*this) *= (*this);
			p >>= 1;
		}
		for (size_t i = 0; i < mat.size(); ++i) mat[i] = res[i];
		return *this;
	}
	Matrix_XOR_AND operator+(const Matrix_XOR_AND& r) const {
		Matrix_XOR_AND res(mat);
		return res += r;
	}
	Matrix_XOR_AND operator*(const Matrix_XOR_AND& r) const {
		Matrix_XOR_AND res(mat);
		return res *= r;
	}
	Matrix_XOR_AND operator*(const BIT_TYPE_Matrix_XOR_AND& r) const {
		Matrix_XOR_AND res(mat);
		return res *= r;
	}
	Matrix_XOR_AND operator^(const size_t& p) const {
		Matrix_XOR_AND res(mat);
		return res ^= p;
	}
	static Matrix_XOR_AND getUnit(size_t n) {
		Matrix_XOR_AND res(n, n, 0);
		for (size_t i = 0; i < n; ++i) res[i][i] = (1LL << 32) - 1;
		return res;
	}
	void show() const {
		for (const auto& r : mat) {
			for (const auto & x : r) {
				std::cerr << x << "\t";
			}
			std::cerr << std::endl;
		}
	}
};