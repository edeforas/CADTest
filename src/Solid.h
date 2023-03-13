#ifndef Solid_
#define Solid_

#include "Mesh.h"
#include "Face.h"

#include <vector>
using namespace std;

///////////////////////////////////////////////////////////////////////////
class Solid
{
public:
	Solid();
	Solid(const Solid& f);
	Solid(const Mesh& m);

	virtual ~Solid();

	Solid& operator=(const Solid& other);

	void add_face(const Face& f);

	Mesh& mesh();

private:
	Mesh _mesh;
	vector<Face> _faces;
};
///////////////////////////////////////////////////////////////////////////

#endif