#include "Surface.h"

#include <cassert>

///////////////////////////////////////////////////////////////////////////
Surface::Surface()
{
	_iColor = 0x808080; //grey
}

Surface::~Surface()
{
}

void Surface::set_color(int iColor)
{
	_iColor = iColor;
}
