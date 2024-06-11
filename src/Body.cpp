#include "Body.h"

///////////////////////////////////////////////////////////////////////////
Body::Body()
{
	clear();
}

Body::~Body()
{ }

void Body::clear()
{
	_faces.clear();
	_iNbSegments = 8;
	_iColor = -1;
}

Transform& Body::transform()
{
	return _transform;
}

vector<Face>& Body::faces()
{
	return _faces;
}

void Body::add_face(const Face& f)
{
	_faces.push_back(f);
}

void Body::set_mesh_precision(int iNbSegments)
{
	_iNbSegments = iNbSegments;
	_mesh.clear(); // must recompute everything next time
}

void Body::set_color(int iColor)
{
	_iColor = iColor;
	_mesh.set_color(_iColor);

	auto& f = faces();
	for (auto& fa : f)
	{
		fa.set_color(iColor);
	}
}
///////////////////////////////////////////////////////////////////////////
const Mesh& Body::mesh()
{
	if (_mesh.empty())
	{
		compute_mesh();
		for (auto& f : _faces)
			_mesh.add_mesh(f.mesh());
	}

	return _mesh;
}
///////////////////////////////////////////////////////////////////////////
void Body::compute_mesh()
{ }
///////////////////////////////////////////////////////////////////////////