#ifndef __MODEL_H__
#define __MODEL_H__

#include <vector>
#include "geometry.h"

class Model {
public:
	Model(const char *filename);
	~Model();
	int nverts();
	int nfaces();
	Vec3f vert(int i);
	std::vector<int> face(int idx);
private:
	std::vector<Vec3f> verts_;
	std::vector<std::vector<int> > faces_;
};

#endif //__MODEL_H__
