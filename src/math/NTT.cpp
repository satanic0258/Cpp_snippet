// Description: 整数列a[i],b[i]から列c[k]=sum{a[i]*b[k-i]}を生成する.任意modに対応.O(NlogN).

namespace NTT {
	std::vector<int> tmp;
	size_t sz = 1;

	inline int powMod(int n, int p, int m) {
		int res = 1;
		while (p) {
			if (p & 1) res = (ll)res * n % m;
			n = (ll)n * n % m;
			p >>= 1;
		}
		return (int)res;
	}
	inline int invMod(int n, int m) {
		return powMod(n, m - 2, m);
	}

	template <int Mod, int PrimitiveRoot>
	struct NTTPart {
		static std::vector<int> ntt(std::vector<int> a, bool inv = false) {
			size_t mask = sz - 1;
			size_t p = 0;
			for (size_t i = sz >> 1; i >= 1; i >>= 1) {
				auto& cur = (p & 1) ? tmp : a;
				auto& nex = (p & 1) ? a : tmp;
				int e = powMod(PrimitiveRoot, (Mod - 1) / sz * i, Mod);
				if (inv) e = invMod(e, Mod);
				int w = 1;
				for (size_t j = 0; j < sz; j += i) {
					for (size_t k = 0; k < i; ++k) {
						nex[j + k] = (cur[((j << 1) & mask) + k] + (ll)w * cur[(((j << 1) + i) & mask) + k]) % Mod;
					}
					w = (ll)w * e % Mod;
				}
				++p;
			}
			if (p & 1) std::swap(a, tmp);
			if (inv) {
				int invSz = invMod(sz, Mod);
				for (size_t i = 0; i < sz; ++i) a[i] = (ll)a[i] * invSz % Mod;
			}
			return a;
		}
		static std::vector<int> mul(std::vector<int> a, std::vector<int> b) {
			a = ntt(a);
			b = ntt(b);
			for (size_t i = 0; i < sz; ++i) a[i] = (ll)a[i] * b[i] % Mod;
			a = ntt(a, true);
			return a;
		}
	};

	constexpr int M[] = {1224736769, 469762049, 167772161};
	constexpr int PR[] = {3, 3, 3};
	constexpr int NTT_CONVOLUTION_TIME = 3;
	/*
		X := max(a)*max(b)*min(|a|, |b|) のとき,
		NTT_CONVOLUTION_TIME <- 1: X <         1224736769 = 1.2*10^ 9 ~ 2^30
		NTT_CONVOLUTION_TIME <- 2: X < 575334854091079681 = 5.8*10^17 ~ 2^59
		NTT_CONVOLUTION_TIME <- 3: X < 2^86 (32bit * 32bit * 10^7くらいまで)
	*/

	inline void garner(std::vector<int> *c, int mod) {
		if (NTT_CONVOLUTION_TIME == 1) {
			for(auto& x : c[0]) x %= mod;
		}
		else if (NTT_CONVOLUTION_TIME == 2) {
			const int r01 = invMod(M[0], M[1]);
			for (size_t i = 0; i < sz; ++i) {
				c[1][i] = (c[1][i] - c[0][i]) * (ll)r01 % M[1];
				if (c[1][i] < 0) c[1][i] += M[1];
				c[0][i] = (c[0][i] + (ll)c[1][i] * M[0]) % mod;
			}
		}
		else if (NTT_CONVOLUTION_TIME == 3) {
			const int R01 = invMod(M[0], M[1]);
			const int R02 = invMod(M[0], M[2]);
			const int R12 = invMod(M[1], M[2]);
			const int M01 = (ll)M[0] * M[1] % mod;
			for (size_t i = 0; i < sz; ++i) {
				c[1][i] = (c[1][i] - c[0][i]) * (ll)R01 % M[1];
				if (c[1][i] < 0) c[1][i] += M[1];
				c[2][i] = ((c[2][i] - c[0][i]) * (ll)R02 % M[2] - c[1][i]) * R12 % M[2];
				if (c[2][i] < 0) c[2][i] += M[2];
				c[0][i] = (c[0][i] + (ll)c[1][i] * M[0] + (ll)c[2][i] * M01) % mod;
			}
		}
	}
	std::vector<int> mul(std::vector<int> a, std::vector<int> b, int mod) {
		for (auto& x : a) x %= mod;
		for (auto& x : b) x %= mod;

		size_t m = a.size() + b.size() - 1;
		sz = 1;
		while (m > sz) sz <<= 1;
		tmp.resize(sz);
		a.resize(sz, 0);
		b.resize(sz, 0);

		std::vector<int> c[NTT_CONVOLUTION_TIME];
		if (NTT_CONVOLUTION_TIME >= 1) c[0] = NTTPart<M[0], PR[0]>::mul(a, b);
		if (NTT_CONVOLUTION_TIME >= 2) c[1] = NTTPart<M[1], PR[1]>::mul(a, b);
		if (NTT_CONVOLUTION_TIME >= 3) c[2] = NTTPart<M[2], PR[2]>::mul(a, b);
		for (auto& v : c) v.resize(m);
		garner(c, mod);
		return c[0];
	}
}; // !!! CHECK NTT_CONVOLUTION_TIME !!!