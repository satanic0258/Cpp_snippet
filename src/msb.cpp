// Description: 入力した64bit整数のMSBを求める．O(1)．

unsigned long long msb(unsigned long long x) {
	x |= x >> 1;
	x |= x >> 2;
	x |= x >> 4;
	x |= x >> 8;
	x |= x >> 16;
	x |= x >> 32;
	return x & ~(x >> 1);
}