#ifndef _OBJMODEL_H_
#define _OBJMODEL_H_
#include <vector>
#include <string>

struct Vector3 {
	float x;
	float y;
	float z;	
};

class ObjModel {

	public:
		ObjModel(const char* file);
		unsigned int facesnum();
		unsigned int verticesnum();
		std::vector<int> getface(unsigned int i);
		Vector3 getvertex(unsigned int i);

	private:
		Vector3 vertex;
		std::vector<Vector3> vertices;
		std::vector<std::vector<int> > faces;
		
};

#endif