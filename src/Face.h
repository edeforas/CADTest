#ifndef _Face_
#define _Face_

#include "Mesh.h"

///////////////////////////////////////////////////////////////////////////
class Face
{
public:
	Face();
	Face(const Face& f);
	Face(const Mesh& m);

	virtual ~Face();

	Face& operator=(const Face& other);

	void set_color(int iColor);

	Mesh& mesh();

private:
	Mesh _mesh;
	int _iColor;
};
///////////////////////////////////////////////////////////////////////////

#endif