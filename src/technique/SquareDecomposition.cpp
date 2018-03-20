// Description: 平方分割テンプレ。

std::vector<int> a(n);

int DIV = std::sqrt(n) + 1;
std::vector<int> seg(n / DIV + 1);

int l, r;
while (l <= r && l%DIV != 0) { // 左にはみ出た部分
	// 何か
	++l;
}
while (l <= r && r%DIV != DIV - 1) { // 右にはみ出た部分
	// 何か
	--r;
}
while (l < r) { // 各セグメント
	// 何か
	l += DIV;
}