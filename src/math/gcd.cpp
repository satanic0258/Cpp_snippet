// Description: ユークリッドの互除法を用いてgcd(a, b)を計算する。O(log(min(a, b)))。

ll gcd(ll a, ll b) {
	return b ? gcd(b, a%b) : a;
}
ll lcm(ll a, ll b) {
	return a / gcd(a, b) * b;
}
