#include <stdio.h>

const int w = 23;
const int h = 12;

int triangle(int x, int y) {
	return abs(x) <= y;
}

int f(int x, int y) {
    // return /* */; // draw a full square
	// draw a circle
	// return (x - 10) * (x - 10) + (y - 10) * (y - 10) <= 8 * 8;
	// draw a triangle
	// return x <= y;
	// draw a big triangle
	// return abs(x - 11) <= y;
	// draw triangle patterns
	// return triangle(x % 6 - 2, y % 3);
	// draw sliced triangle patterns
	// return triangle((x + y / 3 * 3 + 3) % 6 - 2, y % 3);
    // AND of two patterns
    return triangle(x - 11, y) &&
    	   triangle((x + y / 3 * 3 + 3) % 6 - 2, y % 3);
}

int main(int argc, char const *argv[]) {
	int x, y;
	for (y = 0; y < h; ++y) {
		for (x = 0; x < w; ++x) {
			printf(f(x, y) ? "* " : "  ");
		}
		puts("");
	}
	return 0;
}