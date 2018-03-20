// Description: 10進整数dを2進文字列に変換する。O(log_2(d))。

std::string toBinary(ll decimal) {
	if (!decimal) return "0";
	std::string res;
	res.reserve(64);
	while (decimal) {
		res += (decimal & 1) + '0';
		decimal >>= 1;
	}
	std::reverse(res.begin(), res.end());
	return res;
}