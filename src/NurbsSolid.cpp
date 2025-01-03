#include "NurbsSolid.h"

#include "Transform.h"

///////////////////////////////////////////////////////////////////////////
NurbsSolid::NurbsSolid()
{
	clear();
}

NurbsSolid::~NurbsSolid()
{ }

void NurbsSolid::clear()
{
	_surfaces.clear();
}

vector<NurbsSurface>& NurbsSolid::surfaces()
{
	return _surfaces;
}

const vector<NurbsSurface>& NurbsSolid::surfaces() const
{
	return _surfaces;
}

void NurbsSolid::add_surface(const NurbsSurface& ns)
{
	_surfaces.push_back(ns);
}
///////////////////////////////////////////////////////////////////////////
void NurbsSolid::apply_transform(const Transform& t)
{
	for (auto& f: surfaces())
		for (auto &p: f.points())
			t.apply(p);
}
///////////////////////////////////////////////////////////////////////////