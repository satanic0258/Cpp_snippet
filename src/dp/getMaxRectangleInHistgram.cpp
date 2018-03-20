// Description: ヒストグラム内の最大長方形の面積を求める．O(n)．

int getMaxRectangleInHistgram(const std::vector<int>& v) {
	int n = v.size();
	std::stack<int> st;
	std::vector<int> L(n), R(n);
	REP(i, n) {
		while (!st.empty() && v[st.top()] >= v[i]) st.pop();
		L[i] = st.empty() ? 0 : (st.top() + 1);
		st.push(i);
	}
	st = std::stack<int>();
	RREP(i, n) {
		while (!st.empty() && v[st.top()] >= v[i]) st.pop();
		R[i] = st.empty() ? n : st.top();
		st.push(i);
	}
	int max = 0;
	REP(i, n) CHMAX(max, (v[i] + 1) * (R[i] - L[i] + 1));
	return max;
}