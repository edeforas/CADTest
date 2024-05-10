#ifndef NurbsExtrude_
#define NurbsExtrude_

#include "Geometry.h"

class NurbsCurve; 
class NurbsSurface;

///////////////////////////////////////////////////////////////////////////
class NurbsExtrude
{
public:
	NurbsExtrude();
	virtual ~NurbsExtrude();
	bool extrude(const NurbsCurve& nc, const Point3& direction, NurbsSurface& ns) const;

};
///////////////////////////////////////////////////////////////////////////

#endif