#include "Solid.h"

///////////////////////////////////////////////////////////////////////////
Solid::Solid()
{
	clear();
}

Solid::~Solid()
{ }

void Solid::clear()
{
	_surfaces.clear();
}

vector<NurbsSurface>& Solid::surfaces()
{
	return _surfaces;
}

void Solid::add_surface(const NurbsSurface& ns)
{
	_surfaces.push_back(ns);
}
///////////////////////////////////////////////////////////////////////////