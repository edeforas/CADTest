#ifndef NurbsRuled_
#define NurbsRuled_

#include "Geometry.h"

class NurbsCurve; 
class NurbsSurface;

///////////////////////////////////////////////////////////////////////////
class NurbsRuled
{
public:
	NurbsRuled();
	virtual ~NurbsRuled();
	bool rule(const NurbsCurve& nc1, const NurbsCurve& nc2, NurbsSurface& ns) const;

};
///////////////////////////////////////////////////////////////////////////

#endif