// Description: 拡張ユークリッドの互除法を用いてax+by=gcd(a,b)となるx,y,gcd(a,b)を計算する。O(log(max(a,b)))。

ll extgcd(ll a, ll b, ll &x, ll &y) {
	ll g = a; x = 1; y = 0;
	if (b != 0) g = extgcd(b, a % b, y, x), y -= (a / b) * x;
	return g;
}