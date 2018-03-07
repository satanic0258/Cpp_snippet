// Description: 二分法を用いて閾値を計算する。O(logN)。

{ // bisection
	int low = $LOW$, high = $HIGH$;
	auto check = [&](int x) {
        $CHECK$
	};
	while (high - low > 1) {
		int mid = low + (high - low) / 2;
		if (check(mid)) low  = mid;
		else            high = mid;
	}
}