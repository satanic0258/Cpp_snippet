// Description: コンビネーション．前計算O(MAX_N^2)で，参照O(1)．

constexpr int MAX_COMB_N = $max_comb_n$;
int comb[MAX_COMB_N + 1][MAX_COMB_N + 1];
struct InitComb {
	InitComb() {
		comb[0][0] = 1;
		for (int i = 1; i <= MAX_COMB_N; ++i) {
			for (int j = 0; j <= i; ++j) {
				if (j == 0 || j == i) comb[i][j] = 1;
				else comb[i][j] = (comb[i - 1][j - 1] + comb[i - 1][j]) % MOD;
			}
		}
	}
}init_comb;