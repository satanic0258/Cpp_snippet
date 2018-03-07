// Description: LU分解を用いて連立方程式を解く。O(N^3)。

struct LUinfo {
	std::vector<double> value;
	std::vector<int> index;
};
// O( n^3 ), Gaussian forward elimination
LUinfo LU_decomposition(std::vector<std::vector<double>> A) {
	const int n = A.size();
	LUinfo data;
	for (int i = 0; i < n; ++i) {
		int pivot = i;
		for (int j = i + 1; j < n; ++j)
			if (std::abs(A[j][i]) > std::abs(A[pivot][i])) pivot = j;
		std::swap(A[pivot], A[i]);
		data.index.push_back(pivot);
		// if A[i][i] == 0, LU decomposition failed.
		for (int j = i + 1; j < n; ++j) {
			A[j][i] /= A[i][i];
			for (int k = i + 1; k < n; ++k)
				A[j][k] -= A[i][k] * A[j][i];
			data.value.push_back(A[j][i]);
		}
	}
	for (int i = n - 1; i >= 0; --i) {
		for (int j = i + 1; j < n; ++j)
			data.value.push_back(A[i][j]);
		data.value.push_back(A[i][i]);
	}
	return data;
}
// O( n^2 ) Gaussian backward substitution
std::vector<double> LU_backsubstitution(const LUinfo &data, std::vector<double> b) {
	const int n = b.size();
	int k = 0;
	for (int i = 0; i < n; ++i) {
		std::swap(b[data.index[i]], b[i]);
		for (int j = i + 1; j < n; ++j)
			b[j] -= b[i] * data.value[k++];
	}
	for (int i = n - 1; i >= 0; --i) {
		for (int j = i + 1; j < n; ++j)
			b[i] -= b[j] * data.value[k++];
		b[i] /= data.value[k++];
	}
	return b;
}