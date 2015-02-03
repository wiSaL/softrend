#include "tgaimage.h"
#include <iostream>
#include <cmath>
#include <vector>
#include "model.h"
#include "objmodel.h"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);
Model *model = NULL;
ObjModel* mymodel = NULL;

const int width = 800;
const int height = 800;

void line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color);
void line0(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color);

int main(int argc, char** argv) {
	if( argc == 2) {
		model = new Model(argv[1]);
	} else {
		model = new Model("obj/african_head.obj");
		mymodel = new ObjModel("obj/african_head.obj");
	}

	TGAImage image(width, height, TGAImage::RGB);
	
	for (int i = 0; i < model->nfaces(); i++) {
		std::vector<int> face = model->face(i);
		for (int j = 0; j < 3; j++) {
			Vec3f v0 = model->vert(face[j]);
			Vec3f v1 = model->vert(face[(j + 1) % 3]);
			int x0 = (v0.x + 1.) * width / 2.;
			int y0 = (v0.y + 1.) * height / 2.;
			int x1 = (v1.x + 1.) * width / 2.;
			int y1 = (v1.y + 1.) * height / 2;
			line(x0, y0, x1, y1, image, red);
			// line0(x0, y0, x1, y1, image, white);
		}
	}

	for (unsigned int i = 0; i < mymodel->facesnum(); i++ ) {
		std::vector<int> face = mymodel->getface(i);
		for (unsigned int j = 0; j < face.size() ; j++) {
			Vector3 v0 = mymodel->getvertex(face[j]);
			Vector3 v1 = mymodel->getvertex(face[(j + 1) % face.size()]);
			int x0 =  (v0.x + 1.) * width / 2.;
			int y0 =  (v0.y + 1.) * height / 2.;
			int x1 =  (v1.x + 1.) * width / 2.;
			int y1 =  (v1.y + 1.) * height / 2.;

			line(x0, y0, x1, y1, image, white);

		}
	}

	image.flip_vertically();
	image.write_tga_file("output.tga");
	std::cin.get();
	delete model;
	return 0;
}

void line0(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color) {
    bool steep = false;
    if (std::abs(x0 - x1) < std::abs(y0 - y1)) {
        std::swap(x0, y0);
        std::swap(x1, y1);
        steep = true;
    }
    if (x0 > x1) {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }

    for (int x = x0; x <= x1; x ++) {
        float t = (x - x0) / (float) (x1 - x0);
        int y = y0 * (1. - t) + y1 * t;
        if (steep) {
            image.set(y, x, color);
        } else {
            image.set(x, y, color);
        }
    }
}


void line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color) {
	bool steep = false;

	if (std::abs(x0 - x1) < std::abs(y0 - y1)) {
		std::swap(x0, y0);
		std::swap(x1, y1);
		steep = true;
	}

	if (x0 > x1) {
		std::swap(x0, x1);
		std::swap(y0, y1);
	}

	int dx = x1 - x0;
	int dy = y1 - y0;
	int derr = std::abs(dy) * 2;
	int err = 0;
	int y = y0;

	for (int x = x0; x <= x1; x++) {
		if (steep) {
			image.set(y, x, color);
		} else {
			image.set(x, y, color);
		}
		err += derr;

		if (err >= dx) {
			y += (y1 > y0 ? 1 : -1);
			err -= dx * 2;
		}
	}	
} 