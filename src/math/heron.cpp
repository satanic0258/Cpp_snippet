// Description: ヘロンの公式を用いて三角形の面積を計算する。O(1)。

double heron(double a, double b, double c) {
	double s = (a + b + c) / 2;
	return std::sqrt(s*(s - a)*(s - b)*(s - c));
}