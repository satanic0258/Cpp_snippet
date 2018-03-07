// Description: パーミュテーション．前計算O(MAX_N)で，参照O(1)．

constexpr int MAX_PERM_N = $max_perm_n$;
int perm[MAX_PERM_N + 1];
struct InitPerm { 
	InitPerm() {
		perm[0] = 1;
		FOR(i, 1, MAX_PERM_N + 1) perm[i] = perm[i - 1] * i % MOD;
	}
}init_perm;