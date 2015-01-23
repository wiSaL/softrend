#include "tgaimage.h"
#include <iostream>
#include <cmath>

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);

void line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color);

int main(int argc, char** argv) {
	TGAImage image(100, 100, TGAImage::RGB);
	image.set(52, 41, red);
	image.set(1, 1, red);
	image.set(2, 2, red);
	// for (int i = 0; i<1000000; i++) {
		line (10, 20 , 80 , 40, image, red);
		line(20, 10, 40, 80, image, red);
		line(80, 40, 10, 20, image, white);
	// }
	image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
	image.write_tga_file("output.tga");
	std::cin.get();
	return 0;
}

void line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color) {
	bool steep = false;
	if (x0 > x1) {
		std::swap(x0, x1);
		std::swap(y0, y1);
	}

	if (std::abs(x0 - x1) < std::abs(y0 - y1)) {
		std::swap(x0, y0);
		std::swap(x1, y1);
		steep = true;
	}

	int dx = x1 - x0;
	int dy = y1 - y0;
	int derror2 = std::abs(dy)*2;
	int error2 = 0;
	int y = y0;

	for (int x = x0; x <= x1; x++) {
		if (steep) {
			image.set(y, x, color);
		} else {
			image.set(x, y, color);
		}
		error2 += derror2;

		if (error2 > dx) {
			y += (y1 > y0 ? 1 : -1);
			error2 -= dx * 2;
		}
	}
}