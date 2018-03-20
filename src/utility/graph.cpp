// Description: グラフを構築する．

std::vector<std::vector<int>> g($NODE_SIZE$);
REP(i, $m$) {
	--$from$[i]; --$to$[i];
	g[$from$[i]].emplace_back($to$[i]);
	g[$to$[i]].emplace_back($from$[i]);
}