// Description: さいころに関する操作など。

//さいころ
class Dice {
	/* left-hand dice      right-hand dice
			+---+                +---+
			| 1 |                | 1 |
	+---+---+---+---+    +---+---+---+---+
	| 5 | 3 | 0 | 2 |    | 5 | 2 | 0 | 3 |
	+---+---+---+---+    +---+---+---+---+
			| 4 |                | 4 |
			+---+                +---+
	*/
public:
	std::array<int, 6> state;
	Dice(std::array<int, 6> d, bool isRight = false) :state(d) { if (isRight) std::swap(state[2], state[3]); }
	Dice(const Dice& d) :state(d.state) {}
	void rollTo(signed d) {
		/*
			0
			|
		2 --#-- 1
			|
			3
		*/
		std::array<int, 6> tmp(state);
		switch (d) {
		case 0: state[0] = tmp[4]; state[1] = tmp[0]; state[4] = tmp[5]; state[5] = tmp[1]; break;
		case 1: state[0] = tmp[3]; state[2] = tmp[0]; state[3] = tmp[5]; state[5] = tmp[2]; break;
		case 2: state[0] = tmp[2]; state[2] = tmp[5]; state[3] = tmp[0]; state[5] = tmp[3]; break;
		case 3: state[0] = tmp[1]; state[1] = tmp[5]; state[4] = tmp[0]; state[5] = tmp[4]; break;
		}
	}
	void rollTo(char c) {
		switch (c) {
		case 'N': rollTo(0); break;
		case 'E': rollTo(1); break;
		case 'W': rollTo(2); break;
		case 'S': rollTo(3); break;
		}
	}
	void rotate(int d) {
		/* 90d degrees clockwise
		 -> 0 ->
		^   |   v
		2 --#-- 1
		^   |   v
		 <- 3 <-
		*/
		d %= 4;
		std::array<int, 6> tmp(state);
		switch (d) {
		case 0: state[1] = tmp[1]; state[2] = tmp[2]; state[3] = tmp[3]; state[4] = tmp[4]; break;
		case 1: state[1] = tmp[3]; state[2] = tmp[1]; state[3] = tmp[4]; state[4] = tmp[2]; break;
		case 2: state[1] = tmp[4]; state[2] = tmp[3]; state[3] = tmp[2]; state[4] = tmp[1]; break;
		case 3: state[1] = tmp[2]; state[2] = tmp[4]; state[3] = tmp[1]; state[4] = tmp[3]; break;
		}
	}
	bool operator==(const Dice& r)const {
		Dice t(r);
		for (int i = 0; i <= 6; ++i) {
			if (i & 1) t.rollTo('E');
			else    t.rollTo('N');
			for (int j = 0; j < 4; ++j) {
				t.rotate(1);
				if (state == t.state) {
					return true;
				}
			}
		}
		return false;
	}
};