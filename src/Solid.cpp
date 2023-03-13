#include "Solid.h"
#include <cassert>

///////////////////////////////////////////////////////////////////////////
Solid::Solid()
{
}

Solid::Solid(const Solid& f) :
	_mesh(f._mesh)
{
}

Solid::Solid(const Mesh& m) :
	_mesh(m)
{
}

Solid::~Solid()
{
}

Solid& Solid::operator=(const Solid& other)
{
	return *new Solid(*this);
}


Mesh& Solid::mesh()
{
	return _mesh;
}


void Solid::add_face(const Face& f)
{
	_faces.push_back(f);
}