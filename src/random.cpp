// Description: メルセンヌ・ツイスタを用いる乱数生成のテンプレ。

std::random_device rnd;
std::mt19937 mt(rnd());
std::uniform_int_distribution<> rand(/* min */$MIN$, /* max */$MAX$);