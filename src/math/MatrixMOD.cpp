// Description: modを取る行列演算用ライブラリ．

template<class T>
class MatrixMOD {
private:
	std::valarray<std::valarray<T>> mat;
public:
	MatrixMOD(size_t m = 0, size_t n = 0, T init = 0) {
		if (n == 0) n = m;
		mat.resize(m);
		for (size_t i = 0; i < m; ++i) mat[i].resize(n, init);
	}
	MatrixMOD(std::valarray<std::valarray<T>> a) { mat = a; }
	MatrixMOD<T> init(size_t m = 0, size_t n = 0, T init = 0) {
		if (n == 0) n = m;
		mat.resize(m);
		for (size_t i = 0; i < m; ++i) mat[i].resize(n, init);
		return *this;
	}
	std::valarray<T>& operator[](size_t i) { return mat[i]; }
	const std::valarray<T>& operator[](size_t i) const { return mat[i]; }
	MatrixMOD<T>& operator=(const MatrixMOD<T>& r) {
		for (size_t i = 0; i < mat.size(); ++i) mat[i] = r[i];
		return *this;
	}
	MatrixMOD<T> operator+() const { return mat; }
	MatrixMOD<T> operator-() const {
		MatrixMOD<T> res(mat.size());
		for (size_t i = 0; i < mat.size(); ++i) res[i] = (MOD - mat[i]) %= MOD;
		return res;
	}
	MatrixMOD<T>& operator+=(const MatrixMOD<T>& r) {
		for (size_t i = 0; i < mat.size(); ++i) (mat[i] += r[i]) %= MOD;
		return *this;
	}
	MatrixMOD<T>& operator+=(const T& x) {
		for (size_t i = 0; i < mat.size(); ++i) (mat[i] += x) %= MOD;
		return *this;
	}
	MatrixMOD<T>& operator-=(const MatrixMOD<T>& r) { return *this += MOD - r; }
	MatrixMOD<T>& operator-=(const T& x) { return *this += MOD - x; }
	MatrixMOD<T>& operator*=(const MatrixMOD<T>& r) { // O(N^3)
		MatrixMOD<T> res(*this);
		for (size_t i = 0; i < mat.size(); ++i) {
			for (size_t j = 0; j < r[0].size(); ++j) {
				res[i][j] = 0;
				for (size_t k = 0; k < mat[0].size(); ++k) {
					(res[i][j] += mat[i][k] * r[k][j] % MOD) %= MOD;
				}
			}
		}
		return *this = res;
	}
	MatrixMOD<T>& operator*=(const T& x) {
		for (size_t i = 0; i < mat.size(); ++i) (mat[i] *= x) %= MOD;
		return *this;
	}
	MatrixMOD<T>& operator%=(const T& mod) {
		for (size_t i = 0; i < mat.size(); ++i) mat[i] %= MOD;
		return *this;
	}
	MatrixMOD<T>& operator^=(ll p) { // O(N^3 logP)
		MatrixMOD<T> res(*this);

		for (size_t i = 0; i < mat.size(); ++i) {
			for (size_t j = 0; j < mat[0].size(); ++j) {
				res[i][j] = i == j;
			}
		}
		while (p) {
			if (p & 1) (res *= (*this)) %= MOD;
			((*this) *= (*this)) %= MOD;
			p >>= 1;
		}
		for (size_t i = 0; i < mat.size(); ++i) mat[i] = res[i];
		return *this;
	}
	MatrixMOD<T> operator+(const MatrixMOD& r) const {
		MatrixMOD<T> res(mat);
		return res += r;
	}
	MatrixMOD<T> operator-(const MatrixMOD& r) const {
		MatrixMOD<T> res(mat);
		return res -= r;
	}
	MatrixMOD<T> operator*(const MatrixMOD& r) const {
		MatrixMOD<T> res(mat);
		return res *= r;
	}
	MatrixMOD<T> operator*(const T& r) const {
		MatrixMOD<T> res(mat);
		return res *= r;
	}
	MatrixMOD<T> operator^(const int& p) const {
		MatrixMOD<T> res(mat);
		return res ^= p;
	}
	MatrixMOD<T> t() const {
		MatrixMOD<T> res(mat[0].size(), mat.size(), 0);
		for (size_t i = 0; i < mat[0].size(); ++i) {
			for (size_t j = 0; j < mat.size(); ++j) {
				res[i][j] = mat[j][i];
			}
		}
		return res;
	}
	static MatrixMOD<T> getUnit(size_t n) {
		MatrixMOD<T> res(n, n, 0);
		for (size_t i = 0; i < n; ++i) res[i][i] = 1;
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