// Description: 日付関連ライブラリ。

struct Day {
	int M[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int C[12] = {};
	Day() { for (int i = 0; i < 11; ++i) C[i + 1] = C[i] + M[i]; }
	int getDay(int m, int d) {
		return C[m - 1] + d;
	}
	bool is_uruu(int y) {
		return (y % 4 == 0 && y % 100) || y % 400 == 0;
	}
};