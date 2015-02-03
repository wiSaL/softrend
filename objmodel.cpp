#include "objmodel.h"
#include <iostream>
#include <fstream>
#include <sstream>
// #include <string>
// #include <vector>
#include <algorithm>

std::vector<std::string> split (std::string& s);
void repfslash(std:: string& s);

ObjModel::ObjModel(const char* file) {
	std::ifstream in(file);
	std::string str;
	std::stringstream ss;
	std::vector<std::string> fsz;
	std::vector<int> fvertices;
	int x = 0;
	int y = 0;
	int z = 0;
	ss.clear();
	if (in) {
		while ( !in.eof()) {
			std::getline(in, str);
			if (!str.compare(0, 2, "v ")) {
				str.erase(0, 2);
				ss << str;
				ss >> vertex.x;
				ss >> vertex.y;
				ss >> vertex.z;
				vertices.push_back(vertex);
				ss.clear();
			} else if (!str.compare(0, 2, "f ")) {		
				str.erase(0, 2);
				fsz = split(str);
				fvertices.clear();
				for (unsigned int i = 0; i < fsz.size(); i++){
					repfslash(fsz[i]);
					ss.str(fsz[i]);
					ss >> x;
					// ss >> y;
					// ss >> z;
					fvertices.push_back(--x);
					ss.clear();
				}
				faces.push_back(fvertices);
			}
		}
		std::cout << vertices.size() << " : x: " << vertices[1254].x << " y: " 
			<< vertices[1254].y << " z: " << vertices[1254].z << std::endl;
		std::cout << x << " : " << y << " : " << z << std::endl;
		std::cout << faces.size() << " : " << faces[2491][0] << " : " << faces[2491][1] << " : " << faces[2491][2]<< std::endl;
	} else {
		std::cerr << "Fail to open file" << "\n";
	}
}	

unsigned int ObjModel::facesnum() {
	return faces.size();
}

unsigned int ObjModel::verticesnum() {
	return vertices.size();
}

std::vector<int> ObjModel::getface(unsigned int i) { 
	return faces[i];
}

Vector3 ObjModel::getvertex(unsigned int i) {
	return vertices[i];
}

inline bool space (char c) {
	return std::isspace(c);
}

inline bool notspace(char c){
    return !std::isspace(c);
}

std::vector<std::string> split (std::string& s) {
	std::vector<std::string> vec;
	std::string::iterator it = s.begin();
	while (it != s.end()) {
		it = std::find_if(it, s.end(), notspace);
		std::string::iterator j = std::find_if(it, s.end(), space);
		if (it != s.end()) {
			vec.push_back(std::string(it, j));
			it = j;
		}
	}
	return vec;
}

void repfslash(std::string& s) {
	for (std::string::iterator it = s.begin(); it != s.end(); it++) {
		if (*it == '/') 
			*it = ' ';
	}

}