// Description: メビウス関数μ(n)．O(√n)．

int mu(int n) {
	if (n == 1) return 1;
	int re = 1;
	for (int i = 2; i*i <= n; ++i) {
		if (n%i == 0) {
			re *= -1;
			n /= i;
			if (n%i == 0) return 0;
		}
	}
	if (n != 1) re *= -1;
	return re;
}