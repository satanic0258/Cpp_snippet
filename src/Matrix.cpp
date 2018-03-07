// Description: 行列演算用ライブラリ．

template<class T>
class Matrix {
private:
	std::valarray<std::valarray<T>> mat;
public:
	Matrix(size_t m = 0, size_t n = 0, T init = 0) {
		if (n == 0) n = m;
		mat.resize(m);
		for (size_t i = 0; i < m; ++i) mat[i].resize(n, init);
	}
	Matrix(std::valarray<std::valarray<T>> a) { mat = a; }
	Matrix<T> init(size_t m = 0, size_t n = 0, T init = 0) {
		if (n == 0) n = m;
		mat.resize(m);
		for (size_t i = 0; i < m; ++i) mat[i].resize(n, init);
		return *this;
	}
	std::valarray<T>& operator[](size_t i) { return mat[i]; }
	const std::valarray<T>& operator[](size_t i) const { return mat[i]; }
	Matrix<T>& operator=(const Matrix<T>& r) {
		for (size_t i = 0; i < mat.size(); ++i) mat[i] = r[i];
		return *this;
	}
	Matrix<T> operator+() const { return mat; }
	Matrix<T> operator-() const {
		Matrix<T> res(mat.size());
		for (size_t i = 0; i < mat.size(); ++i) res[i] = -mat[i];
		return res;
	}
	Matrix<T>& operator+=(const Matrix<T>& r) {
		for (size_t i = 0; i < mat.size(); ++i) mat[i] += r[i];
		return *this;
	}
	Matrix<T>& operator+=(const T& x) {
		for (size_t i = 0; i < mat.size(); ++i) mat[i] += x;
		return *this;
	}
	Matrix<T>& operator-=(const Matrix<T>& r) { return *this += -r; }
	Matrix<T>& operator-=(const T& x) { return *this += -x; }
	Matrix<T>& operator*=(const Matrix<T>& r) { // O(N^3)
		Matrix<T> res(*this);
		for (size_t i = 0; i < mat.size(); ++i) {
			for (size_t j = 0; j < r[0].size(); ++j) {
				res[i][j] = 0;
				for (size_t k = 0; k < mat[0].size(); ++k) {
					res[i][j] += mat[i][k] * r[k][j];
				}
			}
		}
		return *this = res;
	}
	Matrix<T>& operator*=(const T& x) {
		for (size_t i = 0; i < mat.size(); ++i) mat[i] *= x;
		return *this;
	}
	Matrix<T>& operator^=(ll p) { // O(N^3 logP)
		Matrix<T> res(*this);

		for (size_t i = 0; i < mat.size(); ++i) {
			for (size_t j = 0; j < mat[0].size(); ++j) {
				res[i][j] = i == j;
			}
		}
		while (p) {
			if (p & 1) res *= (*this);
			(*this) *= (*this);
			p >>= 1;
		}
		for (size_t i = 0; i < mat.size(); ++i) mat[i] = res[i];
		return *this;
	}
	Matrix<T> operator+(const Matrix& r) const {
		Matrix<T> res(mat);
		return res += r;
	}
	Matrix<T> operator-(const Matrix& r) const {
		Matrix<T> res(mat);
		return res -= r;
	}
	Matrix<T> operator*(const Matrix& r) const {
		Matrix<T> res(mat);
		return res *= r;
	}
	Matrix<T> operator*(const T& r) const {
		Matrix<T> res(mat);
		return res *= r;
	}
	Matrix<T> operator^(const int& p) const {
		Matrix<T> res(mat);
		return res ^= p;
	}
	Matrix<T> t() const {
		Matrix<T> res(mat[0].size(), mat.size(), 0);
		for (size_t i = 0; i < mat[0].size(); ++i) {
			for (size_t j = 0; j < mat.size(); ++j) {
				res[i][j] = mat[j][i];
			}
		}
		return res;
	}
	double det() const {
		TRY(mat.size() != mat[0].size(), "Matrix is not square.");
		Matrix<double> a(mat.size());
		for (size_t i = 0; i < mat.size(); ++i) {
			for (size_t j = 0; j < mat.size(); ++j) {
				a[i][j] = static_cast<double>(mat[i][j]);
			}
		}
		double d = 1;
		for (int i = 0; i < mat.size(); ++i) {
			int pivot = i;
			for (size_t j = i + 1; j < mat.size(); ++j) {
				if (std::abs(a[j][i]) > std::abs(a[pivot][i])) pivot = j;
			}
			std::swap(a[pivot], a[i]);
			d *= a[i][i] * ((i != pivot) ? -1 : 1);
			if (std::abs(a[i][i]) < EPS) break;
			for (size_t j = i + 1; j < mat.size(); ++j) {
				for (int k = mat.size() - 1; k >= i; --k) {
					a[j][k] -= a[i][k] * a[j][i] / a[i][i];
				}
			}
		}
		return d;
	}
	T tr() const {
		T res = 0;
		for (size_t i = 0; i < mat.size(); ++i) {
			res += mat[i][i];
		}
		return res;
	}
	size_t rank() const {
		Matrix<double> a(mat.size());
		for (size_t i = 0; i < mat.size(); ++i) {
			for (size_t j = 0; j < mat.size(); ++j) {
				a[i][j] = static_cast<double>(mat[i][j]);
			}
		}
		size_t r = 0;
		for (int i = 0; r < static_cast<int>(mat.size()) && i < static_cast<int>(mat[0].size()); ++i) {
			int pivot = r;
			for (size_t j = r + 1; j < mat.size(); ++j) {
				if (std::abs(a[j][i]) > std::abs(a[pivot][i])) pivot = j;
			}
			std::swap(a[pivot], a[r]);
			if (std::abs(a[r][i]) < EPS) continue;
			for (int k = mat[0].size() - 1; k >= i; --k) {
				a[r][k] /= a[r][i];
			}
			for (size_t j = r + 1; j < mat.size(); ++j) {
				for (size_t k = i; k < mat[0].size(); ++k) {
					a[j][k] -= a[r][k] * a[j][i];
				}
			}
			++r;
		}
		return r;
	}
	static Matrix<T> getUnit(size_t n) {
		Matrix<T> res(n, n, 0);
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