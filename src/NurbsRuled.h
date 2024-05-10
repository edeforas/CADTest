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
	bool create_ruled(const NurbsCurve& nc1, const NurbsCurve& nc2, NurbsSurface& ns) const;

};
///////////////////////////////////////////////////////////////////////////

#endif