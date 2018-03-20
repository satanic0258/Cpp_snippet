// Description: 二分法を用いて閾値を計算する。O(repeat)。

{ // bisection double
	double low = $LOW$, high = $HIGH$, repeat = $REPEAT$;
	auto check = [&](double x) {
		$CHECK$
	};
	while (repeat--) {
		double mid = low + (high - low) / 2;
		if (check(mid)) low = mid;
		else            high = mid;
	}
}