// Description: 次数4の閉じたニュートン・コーツの公式を用いて数値積分を行う。計算量O(rep)，誤差o({(b-a)/rep}^7)．

double integ(double a, double b, std::function<double(double)> f) {
	return (b - a)*(
		07 * f((4 * a + 0 * b) / 4.0) +
		32 * f((3 * a + 1 * b) / 4.0) +
		12 * f((2 * a + 2 * b) / 4.0) +
		32 * f((1 * a + 3 * b) / 4.0) +
		07 * f((0 * a + 4 * b) / 4.0)
		) / 90;
}

double integ_rep(double a, double b, int rep, std::function<double(double)> f) {
	double res = 0;
	for (int i = 0; i < rep; ++i) {
		res += integ(a + (b - a) / rep * i, a + (b - a) / rep * (i + 1), f);
	}
	return res;
}