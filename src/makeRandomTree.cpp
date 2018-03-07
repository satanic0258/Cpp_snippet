// Description: ランダムな木を生成する．

#ifdef DEBUG // make random tree
	{
		int n = 30;
		std::mt19937 mt(static_cast<unsigned>(time(nullptr)));
		std::uniform_int_distribution<> randEdge(/* min */1, /* max */n - 1);

		OUT(n)BR;
		FOR(i, 2, n + 1) {
			std::uniform_int_distribution<> rand(1, i - 1);
			OUT(rand(mt))SP OUT(i)BR;
		}

		return 0;
	}
#endif // DEBUG